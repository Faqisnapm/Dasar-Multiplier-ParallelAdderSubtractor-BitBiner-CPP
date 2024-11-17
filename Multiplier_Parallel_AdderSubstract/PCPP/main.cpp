/*
Dibuat Oleh: Faqisna PM & Yogi Andre A.
Note: Masih terdapat memory leak, kemungkinan masalah load dan unload texture pada "obj_Xor.hpp"
Dependencies: Raylib
*/

#include <iostream>
#include <string>
#include "raylib.h"
#include <vector>

#include "Kalkulator.h"
#include "obj_Input_Num.hpp"
#include "obj_Half_Adder.hpp"
#include "obj_Xor.hpp"

//Untuk Resolusi Editor/Debugging
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

//Maksimal bit biner yang ingin dihitung
//Bisa diubah sesuai keinginan
const int Max_Bits = 4;


void Multiplier_Main();
void Full_Adder_Main();
void Full_Substractor_Main();

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Kalkulator Multiplier - Parallel Adder Subtractor | Kelompok 10");

	//Merubah ulang ukuran resolusi window
	int Monitor_Width = 800;
	int Monitor_Height = 600;
	SetWindowSize(Monitor_Width, Monitor_Height);
	SetTargetFPS(60);
	
	while (!WindowShouldClose()) {
		Multiplier_Main();
		Full_Adder_Main();
		Full_Substractor_Main();
	}
	return 0;
}
void Multiplier_Main() {
	std::vector<obj_Input_Num> InputDec, InputBin, OutputBin, OutputDec;
	obj_Input_Num NullNum;
	
	for (int i = 0; i < 2; i++) {
		InputDec.push_back(NullNum);
		InputDec[i].Initialize({ 250.0f + (i * 150) - 10, 300}, {150, 80}, 0, -1);
		InputDec[i].ID = i;
		InputDec[i].DefaultInputBoxCol = LIGHTGRAY;
	}
	for (int i = 0; i < 4; i++) {
		InputBin.push_back(NullNum);
		InputBin[i].Initialize({ 550.0f + (i * 150), 300}, {150, 80}, 0, -1);
		InputBin[i].ID = i;
		InputBin[i].DefaultInputBoxCol = {190, 225, 190, 255};
	}
	for (int i = 0; i < 4; i++) {
		OutputBin.push_back(NullNum);
		OutputBin[i].DisableInput = true;
		OutputBin[i].Initialize({ 1150.0f + (i * 150) + 10, 300 }, { 150, 80 }, 0, -1);
		OutputBin[i].ID = i;
		OutputBin[i].DefaultInputBoxCol = { 190, 190, 255, 255 };
	}
	for (int i = 0; i < 1; i++) {
		OutputDec.push_back(NullNum);
		OutputDec[i].Initialize({ 1750 + 20, 300 }, { 150, 80 }, 0, -1);
		OutputDec[i].ID = i;
		OutputDec[i].DisableInput = true;
		OutputDec[i].DefaultInputBoxCol = { 255, 190, 190, 255 };
	}
	//Label Atas
	InputDec[0].Tulisan_Atas = true;
	InputDec[0].Tulisan_Atas_Str = "A";
	InputDec[1].Tulisan_Atas = true;
	InputDec[1].Tulisan_Atas_Str = "B";

	InputBin[0].Tulisan_Atas = true;
	InputBin[0].Tulisan_Atas_Str = "A1";
	InputBin[1].Tulisan_Atas = true;
	InputBin[1].Tulisan_Atas_Str = "A0";
	InputBin[2].Tulisan_Atas = true;
	InputBin[2].Tulisan_Atas_Str = "B1";
	InputBin[3].Tulisan_Atas = true;
	InputBin[3].Tulisan_Atas_Str = "B0";

	OutputBin[0].Tulisan_Atas = true;
	OutputBin[0].Tulisan_Atas_Str = "O3";
	OutputBin[1].Tulisan_Atas = true;
	OutputBin[1].Tulisan_Atas_Str = "O2";
	OutputBin[2].Tulisan_Atas = true;
	OutputBin[2].Tulisan_Atas_Str = "O1";
	OutputBin[3].Tulisan_Atas = true;
	OutputBin[3].Tulisan_Atas_Str = "O0";

	OutputDec[0].Tulisan_Atas = true;
	OutputDec[0].Tulisan_Atas_Str = "Output";
	OutputDec[0].Tulisan_Atas_Geser_Kiri = 55;

	while (!WindowShouldClose()) {
		//Ratio & Update
		for (auto& i : InputDec) {
			i.Update();
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		}
		for (auto& i : InputBin) {
			i.Update();
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		}
		for (auto& i : OutputBin) {
			i.Update();
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		}
		for (auto& i : OutputDec) {
			i.Update();
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		}
		//Kalkulator
		//Bin ke Dec atau Sebaliknya
		int Num0, Out0_0, Out1_0, Num1, Out0_1, Out1_1;
		if (InputDec[0].OnFocus) {
			Num0 = InputDec[0].NumInputI;
			DecToBin(Num0, Out0_0, Out1_0);
			InputBin[1].NumInputI = Out0_0;
			InputBin[0].NumInputI = Out1_0;
		}
		if(InputBin[0].OnFocus || InputBin[1].OnFocus){
			Out0_0 = InputBin[0].NumInputI;
			Out1_0 = InputBin[1].NumInputI;
			BinToDec(Num0, Out0_0, Out1_0);
			InputDec[0].NumInputI = Num0;
		}
		if (InputDec[1].OnFocus) {
			Num1 = InputDec[1].NumInputI;
			DecToBin(Num1, Out0_1, Out1_1);
			InputBin[3].NumInputI = Out0_1;
			InputBin[2].NumInputI = Out1_1;
		}
		if(InputBin[2].OnFocus || InputBin[3].OnFocus) {
			Out0_1 = InputBin[2].NumInputI;
			Out1_1 = InputBin[3].NumInputI;
			BinToDec(Num1, Out0_1, Out1_1);
			InputDec[1].NumInputI = Num1;
		}
		//Output Biner
		OutputBin[0].NumInputI = (int)Kal_O3(InputBin[1].NumInputI, InputBin[3].NumInputI, InputBin[0].NumInputI, InputBin[2].NumInputI);
		OutputBin[1].NumInputI = (int)Kal_O2(InputBin[1].NumInputI, InputBin[3].NumInputI, InputBin[0].NumInputI, InputBin[2].NumInputI);
		OutputBin[2].NumInputI = (int)Kal_O1(InputBin[1].NumInputI, InputBin[3].NumInputI, InputBin[0].NumInputI, InputBin[2].NumInputI);
		OutputBin[3].NumInputI = (int)Kal_O0(InputBin[1].NumInputI, InputBin[3].NumInputI, InputBin[0].NumInputI, InputBin[2].NumInputI);
		//Output Dec
		std::string ODec0 = std::to_string(OutputBin[0].NumInputI);
		std::string ODec1 = std::to_string(OutputBin[1].NumInputI);
		std::string ODec2 = std::to_string(OutputBin[2].NumInputI);
		std::string ODec3 = std::to_string(OutputBin[3].NumInputI);
		int NumDec = std::stoi(ODec0 + ODec1 + ODec2 + ODec3, nullptr, 2);
		OutputDec[0].NumInputI = InputDec[0].NumInputI * InputDec[1].NumInputI;

		BeginDrawing();
		ClearBackground(WHITE);
		//DrawObject
		for (auto& i : InputDec) i.DrawObject();
		for (auto& i : InputBin) i.DrawObject();
		for (auto& i : OutputBin) i.DrawObject();
		for (auto& i : OutputDec) i.DrawObject();
		EndDrawing();
		if (IsKeyPressed(KEY_P)) break;
	}
}
void Full_Adder_Main() {
	std::vector <obj_Input_Num> InputA, InputB, Output;
	std::vector <obj_Half_Adder> H_OBJ;
	std::vector <obj_Xor> XO;
	obj_Input_Num Carry0;
	obj_Input_Num Carry1;

	int HasilAdderToDec[Max_Bits + 1];
	for (int i = 0; i < Max_Bits + 1; i++) {
		HasilAdderToDec[i] = 0;
	}

	//Inisialisasi Half Adder
	obj_Half_Adder H0;
	for (int i = 0; i < Max_Bits; i++) {
		H_OBJ.push_back(H0);
		H_OBJ[i].Initialize({ 700, float(190.0f * (i * 1.25 + 1)) }, { 200, 140 });
		H_OBJ[i].Label = "Half Adder";
	}

	//Initialize Input
	obj_Input_Num InputA0, InputB0, Output0, OutputAll, OutputDec;

	Carry0.Initialize({ 1100, 50 }, { 150, 80 }, 8, 1);
	Carry0.LabelPinggir = "C";
	Carry0.ID = 0;
	Carry0.WithIdOnLabel = true;

	OutputAll.Initialize({ 1750, GetScreenHeight() / 2.0F }, { 250, 80 }, 8, -1);
	OutputAll.MaxInputLength = Max_Bits + 1;
	OutputAll.LabelPinggir = "Hasil:";
	OutputAll.MultiplierSpace = 25;

	OutputDec.Initialize({ 1750, (GetScreenHeight() / 2.0F) + 80 }, { 250, 80 }, 8, -1);
	OutputDec.MaxInputLength = Max_Bits + 1;
	OutputDec.LabelPinggir = "Dec:";
	OutputDec.MultiplierSpace = 25;

	InputA0.Initialize({ 200, 100 }, { 150, 80 }, 8, 3);
	InputB0.Initialize({ 200, 120 }, { 150, 80 }, 8, 3);
	for (int i = 0; i < Max_Bits; i++) {
		InputA.push_back(InputA0);
		InputB.push_back(InputB0);
	}
	for (int i = 0; i < Max_Bits; i++) {
		InputA[i] = InputA0;
		InputA[i].SetOBJPos(InputA[i].Pos.x, ((i + 1) * 240) - 100);
		InputA[i].ID = i;
		InputA[i].LabelPinggir = "A";
		InputA[i].WithIdOnLabel = true;

		InputB[i] = InputA0;
		InputB[i].SetOBJPos(InputA[i].Pos.x, InputA[i].Pos.y + 100);
		InputB[i].ID = i;
		InputB[i].LabelPinggir = "B";
		InputB[i].WithIdOnLabel = true;
	}

	//Inisialisasi Output
	for (int i = 0; i < Max_Bits; i++) {
		Output.push_back(Output0);
		Output[i].DisableInput = true;
		Output[i].Initialize({ 1300, float(190.0f * (i * 1.25 + 1)) }, { 150, 80 }, 10, 2);
	}

	//Inisialisasi Koneksi Awal
	for (int i = 0; i < Max_Bits; i++) {
		H_OBJ[i].ConnectTo_A(InputA[i]);
		H_OBJ[i].ConnectTo_B(InputB[i]);
		if (i == 0) H_OBJ[i].ConnectTo_C(Carry0);
		if (i < Max_Bits - 1) H_OBJ[i].ConnectTo_CO(H_OBJ[i + 1]);
	}
	Carry1.Initialize({ 1300, Output[Max_Bits - 1].Pos.y + 200 }, { 150, 80 }, 8, 0);
	Carry1.DisableInput = true;
	Carry1.LabelPinggir = "CO";

	while (!WindowShouldClose()) {
		for (auto& i : H_OBJ) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
			i.Update();
		}
		for (auto& i : InputA) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
		}
		for (auto& i : InputB) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
		}
		for (auto& i : Output) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
		}
		Carry0.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		Carry0.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		Carry0.Update();
		Carry1.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		Carry1.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		Carry1.Update();
		OutputAll.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		OutputAll.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		OutputAll.Update();
		OutputDec.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		OutputDec.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		OutputDec.Update();

		//Koneksi Half Adder
		for (int i = 0; i < Max_Bits; i++) {
			H_OBJ[i].ConnectTo_A(InputA[i]);
			H_OBJ[i].ConnectTo_B(InputB[i]);
			if (i == 0) H_OBJ[i].ConnectTo_C(Carry0);
			if (i < Max_Bits - 1) H_OBJ[i].ConnectTo_CO(H_OBJ[i + 1]);
		}
		//Koneksi Carry Output Terakhir
		Carry1.TargetLine = H_OBJ[Max_Bits - 1].Pos_CarryOut;

		//Koneksi Half Adder Ke Output
		for (int i = 0; i < Max_Bits; i++) {
			Output[i].TargetLine = H_OBJ[i].Pos_Output;
		}

		BeginDrawing();
		ClearBackground(WHITE);
		for (int i = 0; i < Max_Bits; i++) {
			InputA[i].DrawObject();
			InputB[i].DrawObject();
			Output[i].DrawObject();
		}
		for (auto& i : H_OBJ) {
			i.Draw();
			i.Draw();
		}
		Carry0.DrawObject();
		Carry1.DrawObject();
		OutputAll.DrawObject();
		OutputDec.DrawObject();
		EndDrawing();

		//Proses Kalkulator
		//Variabel untuk Kalkulasi Paralel Adder
		int A0[Max_Bits], B0[Max_Bits], Hasil[Max_Bits], CarryOut;
		std::string HasilAkhirStr;
		for (int i = 0; i < Max_Bits; i++) {
			A0[i] = InputA[i].NumInputI;
			B0[i] = InputB[i].NumInputI;
		}
		//Kalkulator_Full_Substractor(A0, B0, Hasil, CarryOut, Max_Bits);
		Kalkulator_Full_Adder(A0, B0, Hasil, CarryOut, Max_Bits);
		//Menampilkan Pada Kolom
		Carry1.NumInputI = CarryOut;
		HasilAkhirStr += std::to_string(CarryOut);
		for (int i = 0; i < Max_Bits; i++) {
			Output[i].NumInputI = Hasil[i];
			HasilAkhirStr += std::to_string(Hasil[i]);
		}
		for (int i = 0; i < Max_Bits + 1; i++) {
			if (i == 0) {
				HasilAdderToDec[i] = CarryOut;
			}
			else {
				HasilAdderToDec[i] = Hasil[i - 1];
			}
		}
		OutputDec.NumInputI = BinToDecMulti(HasilAdderToDec, Max_Bits + 1);
		OutputAll.str = HasilAkhirStr;
		if (IsKeyPressed(KEY_P)) break;
	}
	for (auto& i : XO) {
		i.Deinitialize();
	}
}
void Full_Substractor_Main() {
	std::vector <obj_Input_Num> InputA, InputB, Output;
	std::vector <obj_Half_Adder> H_OBJ;
	std::vector <obj_Xor> XO;
	obj_Input_Num Carry0;
	obj_Input_Num Carry1;
	//Inisialisasi Half Adder
	obj_Half_Adder H0;
	for (int i = 0; i < Max_Bits; i++) {
		H_OBJ.push_back(H0);
		H_OBJ[i].Initialize({ 700, float(190.0f * (i * 1.25 + 1)) }, { 200, 140 });
		H_OBJ[i].Label = "Half Substractor";
	}

	//Initialize Input
	obj_Input_Num InputA0, InputB0, Output0, OutputAll, OutputDec;

	Carry0.Initialize({ 1100, 50 }, { 150, 80 }, 8, 1);
	Carry0.LabelPinggir = "C";
	Carry0.ID = 0;
	Carry0.WithIdOnLabel = true;

	OutputAll.Initialize({ 1750, GetScreenHeight() / 2.0F }, { 250, 80 }, 8, -1);
	OutputAll.MaxInputLength = Max_Bits + 1;
	OutputAll.LabelPinggir = "Hasil:";
	OutputAll.MultiplierSpace = 25;

	OutputDec.Initialize({ 1750, (GetScreenHeight() / 2.0F) + 80}, { 250, 80 }, 8, -1);
	OutputDec.MaxInputLength = Max_Bits + 1;
	OutputDec.LabelPinggir = "Dec:";
	OutputDec.MultiplierSpace = 25;

	InputA0.Initialize({ 200, 100 }, { 150, 80 }, 8, 3);
	InputB0.Initialize({ 200, 120 }, { 150, 80 }, 8, 3);
	for (int i = 0; i < Max_Bits; i++) {
		InputA.push_back(InputA0);
		InputB.push_back(InputB0);
	}
	for (int i = 0; i < Max_Bits; i++) {
		InputA[i] = InputA0;
		InputA[i].SetOBJPos(InputA[i].Pos.x, ((i + 1) * 240) - 100);
		InputA[i].ID = i;
		InputA[i].LabelPinggir = "A";
		InputA[i].WithIdOnLabel = true;

		InputB[i] = InputA0;
		InputB[i].SetOBJPos(InputA[i].Pos.x, InputA[i].Pos.y + 100);
		InputB[i].ID = i;
		InputB[i].LabelPinggir = "B";
		InputB[i].WithIdOnLabel = true;
	}

	//Inisialisasi Output
	for (int i = 0; i < Max_Bits; i++) {
		Output.push_back(Output0);
		Output[i].DisableInput = true;
		Output[i].Initialize({ 1300, float(190.0f * (i * 1.25 + 1)) }, { 150, 80 }, 10, 2);
	}

	//Inisialisasi Koneksi Awal
	for (int i = 0; i < Max_Bits; i++) {
		H_OBJ[i].ConnectTo_A(InputA[i]);
		H_OBJ[i].ConnectTo_B(InputB[i]);
		if (i == 0) H_OBJ[i].ConnectTo_C(Carry0);
		if (i < Max_Bits - 1) H_OBJ[i].ConnectTo_CO(H_OBJ[i + 1]);
	}

	Carry1.Initialize({ 1300, Output[Max_Bits - 1].Pos.y + 200 }, { 150, 80 }, 8, 0);
	Carry1.DisableInput = true;
	Carry1.LabelPinggir = "CO";
	obj_Xor XO0;
	for (int i = 0; i < Max_Bits; i++) {
		XO.push_back(XO0);
		XO[i].Initialize();
	}

	while (!WindowShouldClose()) {
		for (auto& i : H_OBJ) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
			i.Update();
		}
		for (auto& i : InputA) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
		}
		for (auto& i : InputB) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
		}
		for (auto& i : Output) {
			i.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
			i.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
			i.Update();
		}
		Carry0.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		Carry0.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		Carry0.Update();
		Carry1.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		Carry1.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		Carry1.Update();
		OutputAll.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		OutputAll.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		OutputAll.Update();
		OutputDec.RatioX = GetScreenWidth() / float(SCREEN_WIDTH);
		OutputDec.RatioY = GetScreenHeight() / float(SCREEN_HEIGHT);
		OutputDec.Update();

		//Koneksi Half Adder
		for (int i = 0; i < Max_Bits; i++) {
			H_OBJ[i].ConnectTo_A(InputA[i]);
			H_OBJ[i].ConnectTo_B(InputB[i]);
			if (i == 0) H_OBJ[i].ConnectTo_C(Carry0);
			if (i < Max_Bits - 1) H_OBJ[i].ConnectTo_CO(H_OBJ[i + 1]);
		}
		//Koneksi Carry Output Terakhir
		Carry1.TargetLine = H_OBJ[Max_Bits - 1].Pos_CarryOut;

		//Koneksi Half Adder Ke Output
		for (int i = 0; i < Max_Bits; i++) {
			Output[i].TargetLine = H_OBJ[i].Pos_Output;
		}
		for (int i = 0; i < Max_Bits; i++) {
			XO[i].SetPos({ InputB[i].LineMiddle.x + (20 * InputB[i].GetRatio()), (InputB[i].LineMiddle.y - (76 * InputB[i].GetRatio())) });
			XO[i].Scale = .125 * InputB[i].GetRatio();
		}

		BeginDrawing();
		ClearBackground(WHITE);
		for (int i = 0; i < Max_Bits; i++) {
			InputA[i].DrawObject();
			InputB[i].DrawObject();
			Output[i].DrawObject();
		}
		for (auto& i : H_OBJ) {
			i.Draw();
			i.Draw();
		}
		Carry0.DrawObject();
		Carry1.DrawObject();
		OutputAll.DrawObject();
		OutputDec.DrawObject();
		for (int i = 0; i < Max_Bits; i++) {
			XO[i].Draw();
		}
		EndDrawing();

		//Proses Kalkulator
		//Variabel untuk Kalkulasi Paralel Adder
		int A0[Max_Bits], B0[Max_Bits], Hasil[Max_Bits], CarryOut;
		std::string HasilAkhirStr;
		for (int i = 0; i < Max_Bits; i++) {
			A0[i] = InputA[i].NumInputI;
			B0[i] = InputB[i].NumInputI;
		}
		Kalkulator_Full_Substractor(A0, B0, Hasil, CarryOut, Max_Bits);
		//Kalkulator_Full_Adder(A0, B0, Hasil, CarryOut, Max_Bits);
		//Menampilkan Pada Kolom
		Carry1.NumInputI = CarryOut;
		//HasilAkhirStr += std::to_string(CarryOut);
		for (int i = 0; i < Max_Bits; i++) {
			HasilAkhirStr += std::to_string(Hasil[i]);
		}
		for (int i = Max_Bits - 1; i >= 0; i--) {
			Output[i].NumInputI = Hasil[(Max_Bits - 1) - i];
		}
		OutputDec.NumInputI = BinToDecMulti(Hasil, Max_Bits);
		OutputAll.str = HasilAkhirStr;
		if (IsKeyPressed(KEY_P)) break;
	}
	for (auto& i : XO) {
		i.Deinitialize();
	}
}

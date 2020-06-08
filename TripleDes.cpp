#include <iostream>
using namespace std;

int IP_Table[64] = {//Initial Permutation
	58,	50,	42,	34,	26,	18,	10,	2,	60,	52,	44,	36,	28,	20,	12,	4,
	62,	54,	46,	38,	30,	22,	14,	6,	64,	56,	48,	40,	32,	24,	16,	8,
	57,	49,	41,	33,	25,	17,	9,	1,	59,	51,	43,	35,	27,	19,	11,	3,
	61,	53,	45,	37,	29,	21,	13,	5,	63,	55,	47,	39,	31,	23,	15,	7 };

int FP_Table[64] = {//Final Permutation
	40,	8,	48,	16,	56,	24,	64,	32,	39,	7,	47,	15,	55,	23,	63,	31,
	38,	6,	46,	14,	54,	22,	62,	30,	37,	5,	45,	13,	53,	21,	61,	29,
	36,	4,	44,	12,	52,	20,	60,	28,	35,	3,	43,	11,	51,	19,	59,	27,
	34,	2,	42,	10,	50,	18,	58,	26,	33,	1,	41,	9,	49,	17,	57,	25 };

int E_Table[48] = {//Extend function	
	32,	1,	2,	3,	4,	5,	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,	28,	29,	30,	31,	32,	1 };	

int P_Table[32] = {//Permutation function
	16,	7,	20,	21,	29,	12,	28,	17,	1,	15,	23,	26,	5,	18,	31,	10,
	2,	8,	24,	14,	32,	27,	3,	9,	19,	13,	30,	6,	22,	11,	4,	25 };

int PC1_Table[56] = {// First permuted checked 
	57,	49,	41,	33,	25,	17,	9,	1,	58,	50,	42,	34,	26,	18,
	10,	2,	59,	51,	43,	35,	27,	19,	11,	3,	60,	52,	44,	36,
	63,	55,	47,	39,	31,	23,	15,	7,	62,	54,	46,	38,	30,	22,
	14,	6,	61,	53,	45,	37,	29,	21,	13,	5,	28,	20,	12,	4 };

int PC2_Table[48] = {// Second permuted checked 
	14,	17,	11,	24,	1,	5,	3,	28,	15,	6,	21,	10,
	23,	19,	12,	4,	26,	8,	16,	7,	27,	20,	13,	2,
	41,	52,	31,	37,	47,	55,	30,	40,	51,	45,	33,	48,
	44,	49,	39,	56,	34,	53,	46,	42,	50,	36,	29,	32 };

int S_Box[8][4][16] = {//8 S-Box
	//S1
	14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7,
	0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8,
	4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0,
	15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13,
	//S2
	15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10,
	3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5,
	0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15,
	13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9,
	//S3
	10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8,
	13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1,
	13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7,
	1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12,
	//S4
	7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15,
	13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9,
	10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4,
	3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14,
	//S5
	2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9,
	14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6,
	4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14,
	11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3,
	// S6
	12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11,
	10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8,
	9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6,
	4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13,
	//S7
	4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1,
	13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6,
	1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2,
	6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12,
	//S8
	13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7,
	1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2,
	7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8,
	2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11 };

string InputText() {
	string text;
	std::cout << "\nPlease input plaintext :" << endl;
	cin >> text;
	return text;
} // InputTest()

string InputCText() {
	string text;
	while (1){
		std::cout << "\nPlease input cipertext(Hex) :" << endl;
		cin >> text;
		if (text.length() % 16 != 0) {
			std::cout << "Error : length\n ";
			continue;
		} // if
		return text;
	} // while
} // InputTest()

void InputKey( char key[], int num ) {
	string tmp;
	while (1) {
		std::cout << "\nPlease input key" << num << "(8 bytes) " << endl;
		cin >> tmp;

		if (tmp.length() != 8) {
			std::cout << "please enter again" << endl;
			continue;
		} // if
		else {
			for (int i = 0; i <= tmp.length(); i++)
				key[i] = tmp[i];
			return;
		} // else 	
		
	} // while
} // InputTest()

void ByteToBit( char text[], int B_int[]) {
	for (int i = 0; i < 8; i++) {
		int num = text[i];
		for (int j = (i+1) * 8-1; j >= i * 8; j--) {
			if (num % 2 == 1) {
				B_int[j] = 1;
				if (num == 1) num = 0;
			} // if
			else B_int[j] = 0;

			num = num / 2;
		} // for
	} // for
} // BytesToBits()

string BitToByte( int B_int[] ) {
	int tmp;
	string text = "";
	for (int i = 0, j = 0; i < 64; i += 8,j++) {
		tmp = B_int[i] * 128 + B_int[i+1] * 64 + B_int[i+2] * 32 + B_int[i+3] * 16 + B_int[i+4] * 8 + B_int[i+5] * 4 + B_int[i+6] * 2 + B_int[i+7]; 
		text += tmp;
	} // for
	return text;
} // BitToByte()

string BinToHex(int bin[]) {
	/*bin 64 bits, hex 16 bits*/
	int dec;
	string hex = "";
	for (int i =0, j = 0; i < 64; i += 4, j++) {
		dec = bin[i] * 8 + bin[i + 1] * 4 + bin[i + 2] * 2 + bin[i + 3];
		if (dec < 10) hex += char(dec+48);
		else if (dec == 10) hex += 'A';
		else if (dec == 11) hex += 'B';
		else if (dec == 12) hex += 'C';
		else if (dec == 13) hex += 'D';
		else if (dec == 14) hex += 'E';
		else if (dec == 15) hex += 'F';
	} // for

	return hex;
} // BinToHex()

void HexToBin(char hex[], int bin[]) {
	string str = "";
	string tmp;
	for (int i = 0; i < 16; i++) {
		if (hex[i] == '0') tmp = "0000";
		else if (hex[i] == '1') tmp = "0001";
		else if (hex[i] == '2') tmp = "0010";
		else if (hex[i] == '3') tmp = "0011";
		else if (hex[i] == '4') tmp = "0100";
		else if (hex[i] == '5') tmp = "0101";
		else if (hex[i] == '6') tmp = "0110";
		else if (hex[i] == '7') tmp = "0111";
		else if (hex[i] == '8') tmp = "1000";
		else if (hex[i] == '9') tmp = "1001";
		else if (hex[i] == 'A' || hex[i] == 'a') tmp = "1010";
		else if (hex[i] == 'B' || hex[i] == 'b') tmp = "1011";
		else if (hex[i] == 'C' || hex[i] == 'c') tmp = "1100";
		else if (hex[i] == 'D' || hex[i] == 'd') tmp = "1101";
		else if (hex[i] == 'E' || hex[i] == 'e') tmp = "1110";
		else if (hex[i] == 'F' || hex[i] == 'f') tmp = "1111";
		str = str + tmp;
	} // for

	for (int i = 0; i < str.length(); i++)
		bin[i] = (int)str[i] - 48;
} // HexToBin()

void Initial_P( int B[]) {
	int tmp[64];
	for (int i = 0; i < 64; i++) tmp[i] = B[IP_Table[i]-1];
	for (int i = 0; i < 64; i++) B[i] = tmp[i];
} // Initial_P()

void Xor(int Array1[], int Array2[], int num) {
	for (int i = 0; i < num; i++) {
		if (Array1[i] == Array2[i]) Array1[i] = 0;
		else Array1[i] = 1;
	} // for
 } // Xor()

void Extend(int input[], int output[]) {
	/*input 32 bits, output 48 bits*/
	for (int i = 0; i < 48; i++) output[i] = input[E_Table[i] - 1];
} // Extend()

void Permutation( int array[]) {
	/*array 32 bits*/
	int tmp[32];
	for (int i = 0; i < 32; i++) tmp[i] = array[P_Table[i] - 1];
	for (int i = 0; i < 32; i++) array[i] = tmp[i];
} // Permutation()

void Rotate(int input[], int output[], int dis) {
	/* input 28 bits, output 28 bits*/
	for (int i = 0; i < 28; i++) output[i] = input[(i + dis) % 28];
} // Rotate()

void Combine(int Array1[], int Array2[], int result[], int num) {
	/*Array1 28 bits, Array2 28 bits, result 56 bits*/
	for (int i = 0, j = num; i < num; i++, j++) {
		result[i] = Array1[i];
		result[j] = Array2[i];
	} // for
} // Combine()

void PC2_Permutation(int input[], int output[]) {
	/*input 56 bits, output 48 bits*/
	for (int i = 0; i < 48; i++) output[i] = input[PC2_Table[i] - 1];
} // PC2_Permutation()

void PC1_Permutation(int input[], int output[]) {
	/*input 64 bits, output 56 bits*/
	for (int i = 0; i < 56; i++) 
		output[i] = input[PC1_Table[i] - 1];
} // PC1_Permutation()

void Sub_Key( int key[64], int sub_key[][48]) { 
	int PC1_Key[56], C[28], D[28];
	int RotateL_c[16][28];
	int RotateL_d[16][28];
	int PC2_Key[48];
	PC1_Permutation(key, PC1_Key);

	for (int i = 0; i < 28; i++) {
		C[i] = PC1_Key[i];
		D[i] = PC1_Key[28 + i];
	} // for

	for (int i = 1; i <= 16; i++) {
		if (i == 1 || i == 2 || i == 9 || i == 16) {
			if (i == 1) {
				Rotate(C, RotateL_c[i - 1], 1);
				Rotate(D, RotateL_d[i - 1], 1);
			} // if 
			else {
				Rotate(RotateL_c[i - 2], RotateL_c[i - 1], 1);
				Rotate(RotateL_d[i - 2], RotateL_d[i - 1], 1);
			} // else
		} // if
		else {
			Rotate(RotateL_c[i - 2], RotateL_c[i - 1], 2);
			Rotate(RotateL_d[i - 2], RotateL_d[i - 1], 2);
		} // else

		Combine(RotateL_c[i - 1], RotateL_d[i - 1], PC1_Key, 28);
		PC2_Permutation(PC1_Key, PC2_Key);
		for (int j = 0; j < 48; j++) sub_key[i - 1][j] = PC2_Key[j];

	} // for

} // Sub_Key() 

void Do_SBox( int num, int input[], int output[]) {
	/*input 6 bits, output 4 bits*/
	int b1b6 = input[0] * 2 + input[5];
	int b2_b5 = input[1] * 8 + input[2] * 4 + input[3] * 2 + input[4];
	int result = S_Box[num][b1b6][b2_b5];
	for (int i = 3; i >= 0; i--) {
		if (result % 2 == 1) {
			output[i] = 1;
			if (result == 1) result = 0;
		} // if
		else output[i] = 0;
		result /= 2;
	} // for
} // Do_SBox

void F_funct( int R[], int sub_key[]) {
	/*R 32 bits, sub_key 48 bits*/
	int Ex_R[48];
	int B_6bits[6];
	int S_4bits[4];
	Extend(R, Ex_R); // correct
	Xor(Ex_R, sub_key, 48);
	for (int num = 0; num < 8; num++) {
		for (int j = num * 6, k = 0; j < (num + 1) * 6; j++, k++) B_6bits[k] = Ex_R[j];
		Do_SBox(num, B_6bits, S_4bits);  //correct
		for (int i = num * 4, k = 0; i < (num + 1) * 4; i++, k++) R[i] = S_4bits[k];
	} // for
	Permutation(R); // correct
} // F_funct

void Final_Permutation(int array[]) {
	/*array 64 bits*/
	int tmp[64];
	for (int i = 0; i < 64; i++) tmp[i] = array[FP_Table[i] - 1];
	for (int i = 0; i < 64; i++) array[i] = tmp[i];
} // Final_Permutation()

void _Des_Encryption( int B[], char key[] ) {
	/*text 8 bits, key 8 bits, ans 16 bytes*/
	int L[32], R[32];
	int sub_key[16][48];
	int B_key[64] = { 0 };
	ByteToBit(key, B_key);
	Sub_Key(B_key, sub_key);  // correct
	Initial_P(B);		// correct

	for (int i = 0, j = 32; i < 32; i++, j++) {
		L[i] = B[i];
		R[i] = B[j];
	} // for

	int Rtmp[32];
	int tmp[32];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 32; j++) Rtmp[j] = R[j];
		F_funct(R, sub_key[i]); // correct
		Xor(L, R, 32);
		for (int j = 0; j < 32; j++) {
			R[j] = L[j];
			L[j] = Rtmp[j];
		} // for
	} // for

	Combine(R, L, B, 32); // correct
	Final_Permutation(B);
} // _Des_Encryption()

void _Des_Decryption(int B[], char key[]) {
	/*B 64 bits, key 8 bits*/
	int L[32], R[32];
	int sub_key[16][48];
	int B_key[64] = { 0 };
	ByteToBit(key, B_key);
	Sub_Key(B_key, sub_key);  // correct	
	Initial_P(B);		// correct

	for (int i = 0, j = 32; i < 32; i++, j++) {
		L[i] = B[i];
		R[i] = B[j];
	} // for

	int Rtmp[32];
	int tmp[32];
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 32; j++) Rtmp[j] = R[j];
		F_funct(R, sub_key[15-i]); // correct
		Xor(L, R, 32);
		for (int j = 0; j < 32; j++) {
			R[j] = L[j];
			L[j] = Rtmp[j];
		} // for
	} // for

	Combine(R, L, B, 32); // correct
	Final_Permutation(B);

} // _Des_Decryption()

void StringToArr(string str, char text[], int init, int num) {
	for (int i = 0; i < num; i++) text[i] = '\0';
	for (int i = init, j = 0; j < num && i < str.length(); i++, j++) 
		text[j] = str[i];
} // StringToArr()

void Create_Key(char key1[], char key2[], char key3[]) {
	int num;
	while (1) {
		std::cout << "\n2 keys or 3 keys :(please enter 2 or 3)" << endl;
		cin >> num;
		if (num != 2 && num != 3) {
			std::cout << "Error number!!\n";
			continue;
		} // if
		break;
	} // while

	if (num == 2) {
		InputKey(key1, 1);
		InputKey(key2, 2);
		for (int i = 0; i < 8; i++) key3[i] = key1[i];
	} // if
	else if (num == 3) {
		InputKey(key1, 1);
		InputKey(key2, 2);
		InputKey(key3, 3);
	} // else if 
} // Create_Key()

void _3Des_Encryption(int B_text[], char key1[], char key2[], char key3[]) {
	_Des_Encryption(B_text, key1);
	_Des_Decryption(B_text, key2);
	_Des_Encryption(B_text, key3);
} // _3Des_Encryption

void _3Des_Decryption(int B_text[], char key1[], char key2[], char key3[]) {
	_Des_Decryption(B_text, key3);
	_Des_Encryption(B_text, key2);
	_Des_Decryption(B_text, key1);
} // _3Des_Decryption

int main()
{
	string Encryption_ans ;
	string Decryption_ans ;
	string H_Decrypt_ans;
	int B_text[64] = { 0 };
	char key[9] = { 0 }, text_8[8] = { 0 }, text_16[16] = { 0 };
	while(1) {
		std::cout << "**********3Des********" << endl;
		std::cout << "*[0]Exit             *" << endl;
		std::cout << "*[1]Des Encrypt      *" << endl;
		std::cout << "*[2]Des Decrypt      *" << endl;
		std::cout << "*[3]3Des Encrypt     *" << endl;
		std::cout << "*[4]3Des Decrypt     *" << endl;
		std::cout << "**********************" << endl;
		std::cout << ": ";
		int choice;
		string all_text;
		Encryption_ans = "";
		Decryption_ans = "";
		H_Decrypt_ans = "";
		cin >> choice;

		if (choice == 0) break;

		else if (choice == 1) {				
			all_text = InputText();
			InputKey(key, 1);
			for (int i = 0; i < all_text.length() - 1; i += 8) {
				StringToArr(all_text, text_8, i, 8);
				ByteToBit(text_8, B_text);
				_Des_Encryption(B_text, key);
				Encryption_ans += BinToHex(B_text);
			} // for
		} // else if 

		else if ( choice == 2) {		
			all_text = InputCText();
			InputKey(key, 1);
			for (int i = 0; i < all_text.length() - 1; i += 16) {
				StringToArr(all_text, text_16, i, 16);
				HexToBin(text_16, B_text);
				_Des_Decryption(B_text, key);
				H_Decrypt_ans += BinToHex(B_text);
				Decryption_ans += BitToByte(B_text);
			} // for
		} // else if 

		else if (choice == 3) {
			char key1[9] = { 0 }, key2[9] = { 0 }, key3[9] = { 0 };
			all_text = InputText();		
			Create_Key(key1, key2, key3);
			for (int i = 0; i < all_text.length() - 1; i += 8) {
				StringToArr(all_text, text_8, i, 8);
				ByteToBit(text_8, B_text);
				_3Des_Encryption(B_text, key1, key2, key3);
				Encryption_ans += BinToHex(B_text);
			} // for
		} // else if
			
		else if (choice == 4) {
			char key1[9] = { 0 }, key2[9] = { 0 }, key3[9] = { 0 };
			all_text = InputCText();
			Create_Key(key1, key2, key3);
			for (int i = 0; i < all_text.length() - 1; i += 16) {
				StringToArr(all_text, text_16, i, 16);
				HexToBin(text_16, B_text);
				_3Des_Decryption(B_text, key1, key2, key3);
				H_Decrypt_ans += BinToHex(B_text);
				Decryption_ans += BitToByte(B_text);
			} // for
		} // else if 
			
		else std::cout << "ERROR !!!!!" << endl; 

		if (choice == 1 || choice == 3) {
			std::cout << "\nYour encrypt text(Hex):" << endl;
			std::cout << Encryption_ans << endl;
			std::cout << endl << endl;
		} // if 
		else if (choice == 2 || choice == 4) {
			std::cout << "\nYour decrypt text(Hex):" << endl;
			std::cout << H_Decrypt_ans << endl;
			std::cout << "\nYour decrypt text(ASCII):" << endl;
			std::cout << Decryption_ans << endl;
			std::cout << endl;
		} // else if 
	} // while

	std::cout << "Thank You!!" << endl;
} // main()



#pragma once
#include<vector>

#define MYSHARED_API _declspec(dllexport)
class ArAPI
{
public:
	ArAPI();
	~ArAPI();
};
struct Color32
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
};

struct myValues
{
	myValues(double px, double py, double pz, double rx, double ry, double rz) : DX(px), DY(py), DZ(pz), RX(rx), RY(ry), RZ(rz) {}
	double DX, DY, DZ, RX, RY, RZ;
};


extern "C"
{
	MYSHARED_API int add(int a, int b);
	MYSHARED_API int startWebcamMonitoring(Color32* raw, int width, int height, myValues* outvalues);
}




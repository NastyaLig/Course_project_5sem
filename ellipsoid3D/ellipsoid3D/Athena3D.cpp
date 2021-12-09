//афинные преобразования в пространстве
#include "StdAfx.h"
#include "Athena2D.h"
//перемещение объекта
CMatrix Translate3D(double x,double y,double z){
	CMatrix m(4,4);
	m(0,0)=1;m(1,1)=1;m(2,2)=1;m(3,3)=1;
	m(0,3)=x;
	m(1,3)=y;
	m(2,3)=z;
	return m;
}
//поворот объекта вокруг оси OZ
CMatrix Rotate3Dz(double fi){
	CMatrix m(4,4);
	double fi_r=fi*pi/180.0;
	m(0,0)=cos(fi_r);
	m(1,1)=cos(fi_r);
	m(2,2)=1;m(3,3)=1;
	m(0,1)=-sin(fi_r);
	m(1,0)=sin(fi_r);
	return m;
}
//поворот объекта вокруг оси OX
CMatrix Rotate3Dx(double fi){
	CMatrix m(4,4);
	double fi_r=fi*pi/180.0;
	m(1,1)=cos(fi_r);
	m(2,2)=cos(fi_r);
	m(0,0)=1;m(3,3)=1;
	m(1,2)=-sin(fi_r);
	m(2,1)=sin(fi_r);
	return m;
}
//поворот объекта вокруг оси OY
CMatrix Rotate3Dy(double fi){
	CMatrix m(4,4);
	double fi_r=fi*pi/180.0;
	m(0,0)=cos(fi_r);
	m(2,2)=cos(fi_r);
	m(1,1)=1;m(3,3)=1;
	m(0,2)=-sin(fi_r);
	m(2,0)=sin(fi_r);
	return m;
}

//векторное произведение векторов
CMatrix VectorMult(CMatrix V1,CMatrix V2){
	CMatrix m(3),a(3,3);
	a(0,1)=-V1(2);
	a(0,2)=V1(1);
	a(1,2)=-V1(0);
	a(1,0)=V1(2);
	a(2,0)=-V1(1);
	a(2,1)=V1(0);
	m=a*V2;
	return m;
}
//скалярное произведение векторов
double ScalarMult(CMatrix V1,CMatrix V2){
	return sqrt(V1(0)*V1(0)+V1(1)*V1(1)+V1(2)*V1(2))*sqrt(V2(0)*V2(0)+V2(1)*V2(1)+V2(2)*V2(2))*(V1(0)*V2(0)+V1(1)*V2(1)+V1(2)*V2(2))/sqrt((V1(0)*V1(0)+V1(1)*V1(1)+V1(2)*V1(2))*(V2(0)*V2(0)+V2(1)*V2(1)+V2(2)*V2(2)));
}
//косинус угла между векторами
double cosViV2(CMatrix V1,CMatrix V2){
	return ScalarMult(V1,V2)/(V1.Abs()*V2.Abs());
}
//преобразование сферических координат в декартовые
CMatrix SphereToCart(CMatrix DView){
	CMatrix Ve(3);
	double fi_r=(270-DView(1))*pi/180;
	double theta_r=DView(2)*pi/180;
	Ve(0)=DView(0)*sin(theta_r)*sin(fi_r);
	Ve(1)=DView(0)*sin(theta_r)*cos(fi_r);
	Ve(2)=DView(0)*cos(theta_r);
	return Ve;
}
//создание матрицы пересчета координат из мировой системы координат в видовую (МСК->ВСК)
CMatrix CreateViewCoord(double R,double fi,double theta){
	CMatrix Ve(4,4),Mz(4,4);
	Mz(0,0)=-1;Mz(1,1)=1;Mz(2,2)=1;Mz(3,3)=1;
	double fi_r=fi*pi/180;
	double theta_r=theta*pi/180;
	Ve=Mz*Rotate3Dx(180-theta)*Rotate3Dz(90-fi);
	return Ve;
}
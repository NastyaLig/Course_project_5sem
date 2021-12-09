#include "StdAfx.h"
#include "CEllipsoid.h"

//прорисовка эллипсоида
void CEllipsoid::DrawEnlighted(CDC& dc,CMatrix& PView,CMatrix& PLight,CRect& RW,COLORREF col,int m){
	//цветоделение на RGB
	double R=GetRValue(col),G=GetGValue(col),B=GetBValue(col);
	//параметры освещенности
	double Kd=1,Ks=1,I=1,Lights=1;
	//перевод сферических координат наблюдателя в декартовы
	CMatrix ViewCart=SphereToCart(PView);
	//перевод сферических координат источнока света в декартовы
	CMatrix LightCart=SphereToCart(PLight);
	//матрица пересчета МСК->ВСК
	CMatrix MV=CreateViewCoord(PView(0),PView(1),PView(2));
	//матрица пересчета ВСК->ОСК
	CMatrix K=SpaceToWindow(rs,RW);
	//точки в ВСК
	CMatrix ViewVert(4,NoV);
	//точки в ОСК
	CPoint MasVert[NoV];
	for(int i=0;i<NoV;i++){
		//пересчет координат точек МСК->ВСК
		CMatrix V=MV*Verticles.GetCol(i);
		V(2)=1;
		//пересчет координат точек ВСК->ОСК
		CMatrix W=K*V.GetCol(0,0,2);
		MasVert[i].x=W(0);
		MasVert[i].y=W(1);
	}
	CMatrix VE(3),R1(3),R2(3),V1(3),V2(3),VN(3);
	double sm;
	//обход верхней "шапки"
	for(int i=0;i<32;i++){
		int k=i+1;
		if(k>=32)k=0;
		R1=Verticles.GetCol(i+1,0,2);	//текущая точка
		R2=Verticles.GetCol(k+1,0,2);	//следующая точка
		VE=Verticles.GetCol(0,0,2);		//самая верхняя точка
		V1=R2-R1;V2=VE-R1;				//ребра грани
		VN=VectorMult(V2,V1);			//вектор нормали
		sm=ScalarMult(VN,ViewCart);		
		if(sm>=0){ //определение видимости грани
			double lsm = ScalarMult(VN, LightCart);
			if(lsm>=0) {	//определение освещенности грани
				//расчет освещенности для диффузионной модели
				if(m==0)Lights=(double)I*Kd*cosViV2(VN,LightCart);
				else if(m==1){
					//расчет освещенности для зеркальной модели
					double P=ScalarMult(VN,LightCart)/(VN.Abs()*VN.Abs());
					Lights=(double)I*Ks*pow(cosViV2(ViewCart,VN*2.0*P-LightCart),20);
				}
			} else Lights = 0;
			CPoint* p=new CPoint[3];
			//получение точек грани
			p[0]=MasVert[k+1];
			p[1]=MasVert[i+1];
			p[2]=MasVert[0];
			//создание кисти расчитанной освещенности
			CBrush* br=new CBrush(RGB(R*Lights,G*Lights,B*Lights));
			dc.SelectObject(br);
			//прорисовка полигона-грани
			dc.Polygon(p,3);
			//освобождение памяти
			delete br;
		}
	}
	//обход боковых граней
	for(int j=1;j<14;j++){
		for(int i=0;i<32;i++){
			int k=i+1;
			if(k>=32)k=0;
			R1=Verticles.GetCol(i+j*32+1,0,2);		//текущая точка
			R2=Verticles.GetCol(k+j*32+1,0,2);		//следующая точка
			VE=Verticles.GetCol(i+(j-1)*32+1,0,2);	//точка предыдущего круга граней
			V1=R2-R1;V2=VE-R1;						//ребра грани			
			VN=VectorMult(V2,V1);					//вектор нормали
			sm=ScalarMult(VN,ViewCart);
			if(sm>=0){ //определение видимости грани
				double lsm = ScalarMult(VN, LightCart);
				if(lsm>=0) {	//определение освещенности грани
					//расчет освещенности для диффузионной модели
					if(m==0)Lights=(double)I*Kd*cosViV2(VN,LightCart);
					else if(m==1){
						//расчет освещенности для зеркальной модели
						double P=ScalarMult(VN,LightCart)/(VN.Abs()*VN.Abs());
						Lights=(double)I*Ks*pow(cosViV2(ViewCart,VN*2.0*P-LightCart),20);
					}
				} else Lights = 0;
				CPoint* p=new CPoint[4];
				//получение точек грани
				p[0]=MasVert[k+j*32+1];
				p[1]=MasVert[i+j*32+1];
				p[2]=MasVert[i+(j-1)*32+1];
				p[3]=MasVert[k+(j-1)*32+1];
				//создание кисти расчитанной освещенности
				CBrush* br=new CBrush(RGB(R*Lights,G*Lights,B*Lights));
				dc.SelectObject(br);
				//прорисовка полигона-грани
				dc.Polygon(p,4);
				//освобождение памяти
				delete br;
			}
		}
		//обход нижней "шапки"
		for(int i=0;i<32;i++){
			int k=i+1;
			if(k>=32)k=0;
			R1=Verticles.GetCol(i+13*32+1,0,2);		//текущая точка
			R2=Verticles.GetCol(k+13*32+1,0,2);		//следующая точка
			VE=Verticles.GetCol(449,0,2);			//самая нижняя точка
			V1=R2-R1;V2=VE-R1;
			VN=VectorMult(V1,V2);					//вектор нормали
			sm=ScalarMult(VN,ViewCart);			
			if(sm>=0){ //определение видимости грани
				double lsm = ScalarMult(VN, LightCart);
				if(lsm>=0) {	//определение освещенности грани
					//расчет освещенности для диффузионной модели
					if(m==0)Lights=(double)I*Kd*cosViV2(VN,LightCart);
					else if(m==1){
						//расчет освещенности для зеркальной модели
						double P=ScalarMult(VN,LightCart)/(VN.Abs()*VN.Abs());
						Lights=(double)I*Ks*pow(cosViV2(ViewCart,VN*2.0*P-LightCart),20);
					}
				} else Lights = 0;

				CPoint* p=new CPoint[3];
				//получение точек грани
				p[0]=MasVert[k+13*32+1];
				p[1]=MasVert[i+13*32+1];
				p[2]=MasVert[449];
				//создание кисти расчитанной освещенности
				CBrush* br=new CBrush(RGB(R*Lights,G*Lights,B*Lights));
				dc.SelectObject(br);
				//прорисовка полигона-грани
				dc.Polygon(p,3);
				//освобождение памяти
				delete br;
			}
		}
	}
}
//конструктор без параметров
CEllipsoid::CEllipsoid(void)
{
	Verticles.RedimMatrix(4,NoV);	//точки в МСК
	int A=200,B=100,C=50,i=1;		//стандартные параметры эллипсоида
	//самая верхняя точка
	Verticles(0,0)=0;				
	Verticles(1,0)=0;
	Verticles(2,0)=-C;
	Verticles(3,0)=1;
	//формирование эллипсов-слоев точек
	for(double beta=-pi/2+pi/16; beta<=pi/2-3*pi/32; beta+=pi/16){	
		//формирование эллипса-слоя на нужной высоте
		for(double alpha=0;alpha<pi*2-pi/32;alpha+=pi/16){			
			Verticles(0,i)=A*cos(beta)*cos(alpha);	//x
			Verticles(1,i)=B*cos(beta)*sin(alpha);	//y
			Verticles(2,i)=C*sin(beta);				//z
			Verticles(3,i)=1;
			i++;
		}
	}
	//самая нижняя точка
	Verticles(0,449)=0;
	Verticles(1,449)=0;
	Verticles(2,449)=C;
	Verticles(3,449)=1;
	//область в МСК
	rs=CRectD(-80,-80,80,80);
}
//конструктор с параметрами
CEllipsoid::CEllipsoid(int a,int b,int c)
{
	Verticles.RedimMatrix(4,NoV);	//точки в МСК
	int A=a,B=b,C=c,i=1;			//заданные параметры эллипсоида
	//самая верхняя точка
	Verticles(0,0)=0;
	Verticles(1,0)=0;
	Verticles(2,0)=-C;
	Verticles(3,0)=1;
	//формирование эллипсов-слоев точек
	for(double beta=-pi/2+pi/16;beta<=pi/2-3*pi/32;beta+=pi/16){
		//формирование эллипса-слоя на нужной высоте
		for(double alpha=0;alpha<pi*2-pi/32;alpha+=pi/16){
			Verticles(0,i)=A*cos(beta)*cos(alpha);	//x
			Verticles(1,i)=B*cos(beta)*sin(alpha);	//y
			Verticles(2,i)=C*sin(beta);				//z
			Verticles(3,i)=1;
			i++;
		}
	}
	//самая нижняя точка
	Verticles(0,449)=0;
	Verticles(1,449)=0;
	Verticles(2,449)=C;
	Verticles(3,449)=1;
	//область в МСК
	rs=CRectD(-80,-80,80,80);
}

CEllipsoid::~CEllipsoid(void)
{
}

/*******************************************************************\
 * Comment(s)    : ���������� ���� �������. ������������            *
 *                 ����������� �������						        *
 *                 ������ ����������						        *
 *                                                                  *
 |******************************************************************/

#include <windows.h>
#include "Point05_03.h"	//���������� �������
#include <iostream>

 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 /*   � � � � � � � � � �   � � � � � � � � � �  �  � � � � � � � � �   */
 /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
  //���������� ���������� ����� � ���� ������: Point05_03.cpp � Ex05_03_Con.cpp
  //������� ��������� ���������� ����������
extern HDC hdc;      // �������  �������� ����������

// ������ ��� �������� ��������� ���������� � �� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

	/*----------------------------------------------------------------*/
	/*             � � � � � � � � � �    � � � � � � �               */
	/*----------------------------------------------------------------*/

			/*----------------------------------------*/
			/*        ������ ������ Location          */
			/*----------------------------------------*/

Location::Location(int InitX, int InitY) //�����������
{
	//������������� �������� ���������� ������ ������
	X = InitX;
	Y = InitY;
};//end Location::Location()

int Location::GetX(void)  //�������� X ���������� �����
{
	return X;
};//end Location::GetX()	

int Location::GetY(void) //�������� Y ���������� �����
{
	return Y;
}; //end Location::GetY()

			/*----------------------------------------*/
			/*        ������ ������ Point             */
			/*----------------------------------------*/

//��� ������������� �������� ����� ���������� ����������� ������
Point::Point(int InitX, int InitY) : Location(InitX, InitY) //�����������
{ }//end Point::Point()

void Point::Show(void)  //�������� �����
{
	SetPixel(hdc, X, Y, RGB(255, 0, 0));	//������ ������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	// 4 ����� ��� ��������
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}//end Point::Show()
 //--------------------------------------------------------------
void Point::Hide(void)  //������ �����
{
	SetPixel(hdc, X, Y, RGB(0, 0, 255));//������ ����� ������ ��� ����
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 255));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 255));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 255));
}//end Point::Hide()
 //--------------------------------------------------------------
void Point::MoveTo(int NewX, int NewY) //����������� �����
{
	Hide();		//������� ����� ���������
	X = NewX;	//�������� ���������� �����
	Y = NewY;
	Show();		//�������� ����� �� ����� �����
};//end Point::MoveTo()

void Point::Drag(int Step) //����������� �����
{
	int FigX, FigY; // ����� ���������� ������
	FigX = GetX();    //�������� ��������� ��������� ������
	FigY = GetY();

	while (1)	//����������� ���� ���������� ������
	{
		if (KEY_DOWN(VK_ESCAPE))     //����� ������ 27 ������
			break;
		//����������� �������� �������
		if (KEY_DOWN(VK_LEFT)) //������� �����  37
		{
			FigX -= Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//end if
		if (KEY_DOWN(VK_RIGHT)) //������� ������  39
		{
			FigX += Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//end if
		if (KEY_DOWN(VK_DOWN)) //������� ����  40
		{
			FigY += Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//end if

		if (KEY_DOWN(VK_UP)) //������� �����  38
		{
			FigY -= Step;
			MoveTo(FigX, FigY);
			Sleep(100);
		}//end if
	}   //while

};//end Point::Drag()

		/*----------------------------------------*/
		/*        ������ ������ Circle            */
		/*----------------------------------------*/

//��� ������������� �������� ����� ���������� ����������� ������
Car::Car(int InitX, int InitY, int InitSpeed) : Point(InitX, InitY) // ����������� Circle
{
	Speed = InitSpeed; //������������� �������� ���������� ������ ������
}//end Car::Car ()

void Car::Show(void) // �������� ����
{
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������

	// �������� ���� ������������� ������
	Rectangle(hdc, X - 100, Y - 70, X - 280, Y - 140);
	Rectangle(hdc, X, Y, X - 370, Y - 70);
	Ellipse(hdc, X - 115, Y + 35, X - 45, Y - 35);
	Ellipse(hdc, X - 325, Y + 35, X - 255, Y - 35);
	// ��������� ���� ��������� �������  
	DeleteObject(Pen);

} // end Car::Show()

void Car::Hide(void) // ������ ����
{
	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	SelectObject(hdc, Pen);	//������� ���� ��������

	// �������� ���� ������������� ������
	Rectangle(hdc, X - 100, Y - 70, X - 280, Y - 140);
	Rectangle(hdc, X, Y, X - 370, Y - 70);
	Ellipse(hdc, X - 115, Y + 35, X - 45, Y - 35);
	Ellipse(hdc, X - 325, Y + 35, X - 255, Y - 35);
	// ��������� ���� ��������� �������  
	DeleteObject(Pen);

}// end Car::Hide()

void Car::MoveTo(int NewX, int NewY) // ��������� � ������������ ����� ����������
{
	Hide();  //�������� ������ ����������
	X = NewX; //�������� ����������
	Y = NewY;
	Show();  //�������� ���������� �� ����� �����
}//end Car::MoveTo()

/* �����  ������ ��������� ����������� ��������    !!*/
/*void Car::Drag(int Step) // ����������� ������
{
	int FigX, FigY; // ����� ���������� ������

	FigX = GetX();    //�������� ��������� ��������� ������
	FigY = GetY();

	while (1)	//����������� ���� ���������� ������
	{
		if (KEY_DOWN(VK_ESCAPE))     //����� ������ 27 escape
		{
			std::cout << "FigX = " << GetX();
			break;
		}
		//����������� �������� �������

		if (KEY_DOWN(VK_LEFT)) //������� �����  37
		{
			FigX -= Speed;
			MoveTo(FigX, FigY);
			Sleep(500);
		}//end if

		if (KEY_DOWN(VK_RIGHT)) //������� ������  39
		{
			FigX += Speed;
			MoveTo(FigX, FigY);
			Sleep(500);
		}//end if

		if (KEY_DOWN(VK_DOWN)) //������� ����  40
		{
			FigY += Speed;
			MoveTo(FigX, FigY);
			Sleep(500);
		}//end if

		if (KEY_DOWN(VK_UP)) //������� �����  38
		{
			FigY -= Speed;
			MoveTo(FigX, FigY);
			Sleep(500);
		}//end if
	}//end while
} //end Car::Drag()
*/

/**************   End of File Point05_03.�PP   ********************/

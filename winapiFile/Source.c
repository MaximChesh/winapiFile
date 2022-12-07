#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <Windows.h>

void raschet(float, float, float);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HANDLE file = CreateFile(L"input.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	float a, b, c;
	a = 0;
	b = 0;
	c = 0;
	int mass[] = { a,b,c };
	DWORD size = 100, bytes;
	char text[254];
	if (file != INVALID_HANDLE_VALUE) {
        ReadFile(file, text, size, &bytes, NULL);
        //A
        int schetNumA = 0;
        for (int i = 0; i < 254; i++)
        {
            if (text[i] != 32) {
                schetNumA++;
            }
            else {
                break;
            }
        }
        int NumAone = 1;
        int NumAtwo = 1;
        double schetA = 0;
        for (int i = schetNumA - 1; i >= 0; i--) {
            if (text[i] == 46) {
                for (int j = 0; j < schetNumA - 1; j++) {
                    NumAone = NumAone * 10;
                }
                a = a / NumAone;
            }
            else {
                if (text[0] == 45)
                {
                    if (text[i] != 45)
                    {
                        schetA = text[i] - '0';
                        a += schetA * NumAtwo;
                        NumAtwo = NumAtwo * 10;
                    }
                    else
                    {
                        a = -1 * a;
                    }
                }
                else
                {
                    schetA = text[i] - '0';
                    a += schetA * NumAtwo;
                    NumAtwo = NumAtwo * 10;
                }
            }
        }

        //B
        int schetNumB = schetNumA;
        for (int i = schetNumB + 1; i < 255; i++) {
            if (text[i] != 32)
            {
                schetNumB++;
            }
            else
            {
                break;
            }
        }
        int NumBone = 1;
        int NumBtwo = 1;
        double schetB = 0;
        for (int i = schetNumB; i >= schetNumA + 1; i--) {
            if (text[i] == 46) {
                for (int j = 0; j < schetNumB - 1; j++) {
                    NumBone = NumBone * 10;
                }
                a = a / NumBone;
            }
            else {
                if (text[0] == 45)
                {
                    if (text[i] != 45)
                    {
                        schetB = text[i] - '0';
                        b += schetB * NumBtwo;
                        NumBtwo = NumBtwo * 10;
                    }
                    else
                    {
                        b = b * -1;
                    }
                }
                else
                {
                    schetB = text[i] - '0';
                    b += schetB * NumBtwo;
                    NumBtwo = NumBtwo * 10;
                }
            }
        }

        //C
        int schetNumC = schetNumB;
        for (int i = schetNumC + 1; i < 255; i++) {
            if (text[i] != -52)
            {
                schetNumC++;
            }
            else
            {
                break;
            }
        }
        int NumCone = 1;
        int NumCtwo = 1;
        double schetC = 0;
        for (int i = schetNumC; i >= schetNumB + 2; i--) {
            if (text[i] == 46) {
                for (int j = 0; j < schetNumC - 1; j++) {
                    NumCone = NumCone * 10;
                }
                c = c / NumCone;
                NumCtwo = 1;
            }
            else {
                if (text[0] == 45)
                {
                    if (text[i] != 45)
                    {
                        schetC = text[i] - '0';
                        c += schetC * NumCtwo;
                        NumCtwo = NumCtwo * 10;
                    }
                    else
                    {
                        c = c * -1;
                    }
                }
                else
                {
                    schetC = text[i] - '0';
                    c += schetC * NumCtwo;
                    NumCtwo = NumCtwo * 10;
                }
            }
        }
	}

    int schet = 0;
    int schetspace = 0;
    if ((file = fopen("input.txt", "r"))) {
        fgets(text, 254, file);
        for (int k = 0; k < 254; k++) {
            if (text[k] == 32) {
                schetspace++;
            }
            if (text[k] >= 48 && text[k] <= 57) {
            }
            else if (text[k] == -52 || text[k] == 0 || text[k] == 32 || text[k] == 46) {
            }
            else {
                schet++;
                break;
            }
            if (schetspace > 2) {
                schet++;
                break;
            }
        }
    }

    if (schet == 0) {
        raschet(a, b, c);
    }
    else {
        HANDLE answer = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        fprintf(answer, "Неверно введены значения\nКорней нет");
    }
}

void raschet(float a, float b, float c) {
    HANDLE answer = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    char text[300];
    DWORD bytes;
    int size = 0;
    float d, x1, x2;

    d = (b * b) - 4 * a * c;
    //WriteFile(answer, "Дискриминант: %f\n", d, 50, &bytes, NULL);

    if (d > 0) {
        x1 = (-b + sqrt(d)) / (2 * a);
        x2 = (-b - sqrt(d)) / (2 * a);
        sprintf(text, "Дискриминант: %f\nx1=%f\nx2=%f", d, x1, x2);
        while (text[size] != 0) {
            size++;
        }
        WriteFile(answer, text, size, &bytes, NULL);
    }
    else if (d < 0) {
        sprintf(text, "Дискриминант: %f\nКорней нет", d);
        while (text[size] != 0) {
            size++;
        }
        WriteFile(answer, text, size, &bytes, NULL);
    }
    else if (d == 0) {
        x1 = (-b + sqrt(d)) / (2 * a);
        sprintf(text, "Дискриминант: %f\nx1=%f", d, x1);
        while (text[size] != 0) {
            size++;
        }
        WriteFile(answer, text, size, &bytes, NULL);
    }
}
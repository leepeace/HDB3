#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

void printResult(char);//��� ���
void HDB3ConversionDigital(int);
void ConversionSignal(int);//0000���� �ٲ�
void FromSignalToData(int);//signal->data��ȯ
void FromDataToSignal(int);//data->signal��ȯ

char inputDigital[50];//�Է� ��
char changeDigital[50];//��� ��
char operator;//���� ������
int NotZeroCount = 0;//0�� �ƴ� ��� count

int main(void)
{
	char prefix;//���������� ��ȣ���� ����

	scanf("%c %s",&prefix,inputDigital);

	int DataSize = sizeof(inputDigital)/sizeof(char);
	
	if (prefix == 'D') {//input�� �������� ��� ������ ������->������ ��ȣ
		FromDataToSignal(DataSize);
	}
	else if(prefix == 'S'){//input�� signal�� ��� ������ ��ȣ->������ ������
		FromSignalToData(DataSize);
	}
	else {
		;
	}

	printResult(prefix);//��ȯ ��� ���

	return 0;
}
void HDB3ConversionDigital(int index)
{
	//0�� �ƴ� ������ Ȧ����
	if (NotZeroCount % 2 == 1) {
		//000V
		changeDigital[index] = '0';
		changeDigital[index + 1] = '0';
		changeDigital[index + 2] = '0';
		
		if (operator == '-') {//����
			changeDigital[index + 3] = '-';
			operator = '-';
		}
		else if(operator == '+'){//����
			changeDigital[index + 3] = '+';
			//printf("change : %c \n", changeDigital[index + 3]);
			operator = '+';
		}
		NotZeroCount++;
	}//end of if
	//0�� �ƴ� ������ ¦����
	else {
		//BOOV
		if (operator == '-') {//�ؼ�
			changeDigital[index] = '+';
			operator = '+';
		}
		else if(operator == '+'){//�ؼ�
			changeDigital[index] = '-';
			operator = '-';
		}
		changeDigital[index + 1] = '0';
		changeDigital[index + 2] = '0';
		if (operator == '-') {//����
			changeDigital[index + 3] = '-';
			operator = '-';
		}
		else if(operator == '+'){//����
			changeDigital[index + 3] = '+';
			operator = '+';
		}
		NotZeroCount += 2;
	}//end of else

}
void printResult(char JudgePrefix)
{
	int size = sizeof(changeDigital)/sizeof(char);
	if (JudgePrefix == 'D') {
		JudgePrefix = 'S';
	}
	else if (JudgePrefix == 'S') {
		JudgePrefix = 'D';
	}
	printf("%c ", JudgePrefix);
	for (int i = 0; i < size; i++) {
		printf("%c", changeDigital[i]);
	}
	putchar('\n');
}
void ConversionSignal(int index)
{
	for (int i = 0; i < 4; i++) {
		changeDigital[index + i] = '0';
	}
}
void FromSignalToData(int DataSize)
{
	int judgeSignal = 0;
	int JudgeNumber = 0;
		//OOOV
	for (int l = 0; l < DataSize; l++) {
		if (judgeSignal == 0) {
			if (l == DataSize - 4 - 1) {
				judgeSignal = 1;//�������� ���� l < DataSize - 4������ ����
			}
			if (JudgeNumber % 2 == 1) {//0�� �ƴ� ������ Ȧ����
				if (inputDigital[l] == '0' && inputDigital[l + 1] == '0' &&
					inputDigital[l + 2] == '0' && inputDigital[l + 3] == '-') {
					ConversionSignal(l);
					JudgeNumber++;
					l = l + 3;
				}
				else if (inputDigital[l] == '0' && inputDigital[l + 1] == '0' &&
					inputDigital[l + 2] == '0' && inputDigital[l + 3] == '+') {
					ConversionSignal(l);
					JudgeNumber++;
					l = l + 3;
				}
				else {
					if (inputDigital[l] == '0') {
						changeDigital[l] = '0';
					}
					else if (inputDigital[l] == '+' || inputDigital[l] == '-') {
						changeDigital[l] = '1';
						JudgeNumber++;
					}
				}
			}
			else if (JudgeNumber % 2 == 0) {
				if (inputDigital[l] == '+' && inputDigital[l + 1] == '0' &&
					inputDigital[l + 2] == '0' && inputDigital[l + 3] == '+') {
					ConversionSignal(l);
					JudgeNumber += 2;
					l = l + 3;
				}
				else if (inputDigital[l] == '-' && inputDigital[l + 1] == '0' &&
					inputDigital[l + 2] == '0' && inputDigital[l + 3] == '-') {
					ConversionSignal(l);
					JudgeNumber += 2;
					l = l + 3;
				}
				else {
					if (inputDigital[l] == '0') {
						changeDigital[l] = '0';
					}
					else if (inputDigital[l] == '+' || inputDigital[l] == '-') {
						changeDigital[l] = '1';
						JudgeNumber++;
					}
				}
			}
		}//end of if
		else {
			if (inputDigital[l] == '0') {
				changeDigital[l] = '0';
			}
			else if (inputDigital[l] == '+' || inputDigital[l] == '-') {
				changeDigital[l] = '1';
				JudgeNumber++;
			}
		}
	}//end of for

}
void FromDataToSignal(int DataSize)
{
	int zeroCount = 0;
	int judgeData = 0;
	int index = 0;
	for (int i = 0; i < DataSize; i++) {
		//0�� ���������� 4���� ����
		if (judgeData == 0 && inputDigital[i] == '0' && inputDigital[i + 1] == '0'
			&& inputDigital[i + 2] == '0'&&inputDigital[i + 3] == '0') {
			zeroCount = i;//0�� ���������� ������ �κ��� ù��° �ε���

			HDB3ConversionDigital(zeroCount);

			operator = changeDigital[i + 3];
			if (i == DataSize - 4 - 1) {
				judgeData = 1;//�������� ���ڴ� i < DataSize - 4�϶������� ����
			}
			i = i + 3;//0�� ���������� 4�� ������ �κ��� �ٷ� �� �������� ����
		}

		else if (inputDigital[i] == '1') {
			NotZeroCount++;
			if (NotZeroCount == 1) {
				changeDigital[i] = '+';
				operator = '+';
			}
			else if (operator == '+') {
				changeDigital[i] = '-';
				operator = '-';
			}
			else if (operator == '-') {
				changeDigital[i] = '+';
				operator = '+';
			}
		}
		else if (inputDigital[i] == '0') {
			zeroCount++;
			changeDigital[i] = '0';
		}
	}//end of if
}
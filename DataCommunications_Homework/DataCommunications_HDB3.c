#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

void printResult(char);//결과 출력
void HDB3ConversionDigital(int);
void ConversionSignal(int);//0000으로 바꿈
void FromSignalToData(int);//signal->data변환
void FromDataToSignal(int);//data->signal변환

char inputDigital[50];//입력 값
char changeDigital[50];//결과 값
char operator;//현재 연산자
int NotZeroCount = 0;//0이 아닌 경우 count

int main(void)
{
	char prefix;//데이터인지 신호인지 구분

	scanf("%c %s",&prefix,inputDigital);

	int DataSize = sizeof(inputDigital)/sizeof(char);
	
	if (prefix == 'D') {//input이 데이터인 경우 디지털 데이터->디지털 신호
		FromDataToSignal(DataSize);
	}
	else if(prefix == 'S'){//input이 signal인 경우 디지털 신호->디지털 데이터
		FromSignalToData(DataSize);
	}
	else {
		;
	}

	printResult(prefix);//변환 결과 출력

	return 0;
}
void HDB3ConversionDigital(int index)
{
	//0이 아닌 개수가 홀수개
	if (NotZeroCount % 2 == 1) {
		//000V
		changeDigital[index] = '0';
		changeDigital[index + 1] = '0';
		changeDigital[index + 2] = '0';
		
		if (operator == '-') {//위반
			changeDigital[index + 3] = '-';
			operator = '-';
		}
		else if(operator == '+'){//위반
			changeDigital[index + 3] = '+';
			//printf("change : %c \n", changeDigital[index + 3]);
			operator = '+';
		}
		NotZeroCount++;
	}//end of if
	//0이 아닌 개수가 짝수개
	else {
		//BOOV
		if (operator == '-') {//준수
			changeDigital[index] = '+';
			operator = '+';
		}
		else if(operator == '+'){//준수
			changeDigital[index] = '-';
			operator = '-';
		}
		changeDigital[index + 1] = '0';
		changeDigital[index + 2] = '0';
		if (operator == '-') {//위반
			changeDigital[index + 3] = '-';
			operator = '-';
		}
		else if(operator == '+'){//위반
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
				judgeSignal = 1;//연속적인 경우는 l < DataSize - 4까지만 구함
			}
			if (JudgeNumber % 2 == 1) {//0이 아닌 개수가 홀수개
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
		//0이 연속적으로 4개가 나옴
		if (judgeData == 0 && inputDigital[i] == '0' && inputDigital[i + 1] == '0'
			&& inputDigital[i + 2] == '0'&&inputDigital[i + 3] == '0') {
			zeroCount = i;//0이 연속적으로 나오는 부분의 첫번째 인덱스

			HDB3ConversionDigital(zeroCount);

			operator = changeDigital[i + 3];
			if (i == DataSize - 4 - 1) {
				judgeData = 1;//연속적인 숫자는 i < DataSize - 4일때까지만 구함
			}
			i = i + 3;//0이 연속적으로 4번 나오는 부분의 바로 그 다음부터 시작
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
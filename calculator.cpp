#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define dx 0.01
#define _CRT_SECURE_NO_WARNINGS


struct shuju {
	double data[100];
	int top;
};


struct fuhao {
	char symbol[100];
	int top;
};


void InitOperateNum(struct shuju *StackNum)
{
	StackNum->top = -1;
}


void InitOperateSymbol(struct fuhao *StackSymbol)
{
	StackSymbol->top = -1;
}


void Inshuju(struct shuju *StackNum, double num)
{
	StackNum->top++;
	StackNum->data[StackNum->top] = num;
}


void Infuhao(struct fuhao *StackSymbol, char ch)
{
	StackSymbol->top++;
	StackSymbol->symbol[StackSymbol->top] = ch;
}


double Randshuju(struct shuju *StackNum)
{
	return StackNum->data[StackNum->top];
}


char Randfuhao(struct fuhao *StackSymbol)
{
	return StackSymbol->symbol[StackSymbol->top];
}


double Putshuju(struct shuju *StackNum)
{
	double x;
	x = StackNum->data[StackNum->top];
	StackNum->top--;
	return x;
}


char Putfuhao(struct fuhao *StackSymbol)
{
	char c;
	c = StackSymbol->symbol[StackSymbol->top];
	StackSymbol->top--;
	return c;
}


int judge(char ch) {
	if (ch == '(') {
		return 1;
	}
	if (ch == '+' || ch == '-') {
		return 2;
	}
	else if (ch == '*' || ch == '/') {
		return 3;
	}
	else if (ch == ')') {
		return 4;
	}
}


double Math(double v1, double v2, char c)
{
	double sum = 0;
	switch (c) {
	case '+': {
		sum = v1 + v2;
		break;
	}
	case '-': {
		sum = v1 - v2;
		break;
	}
	case '*': {
		sum = v1 * v2;
		break;
	}
	case '/': {
		sum = v1 / v2;
		break;
	}
	}

	return sum;
}


double pnc(char _str[])
{
	struct shuju data;
	struct fuhao symbol;
	InitOperateNum(&data);
	InitOperateSymbol(&symbol);
	int i, t;
	double sum = 0, v1, v2;
	//char c;
	i = t = 0;
	char v[100] = { 0 };
	char *str = (char *)malloc(sizeof(char) * 200);
	while (_str[i] != '\0') {
		str[i] = _str[i];
		i++;
	}
	str[i] = '\0';
	for (i = 0; str[i] != '\0'; i++) {
		if (i == 0 && str[i] == '-') {
			v[t++] = str[i];
		}
		else if (str[i] == '(' && str[i + 1] == '-') {
			i++;
			v[t++] = str[i++];
			while (str[i] >= '0' && str[i] <= '9') {
				v[t] = str[i];
				t++;
				i++;
			}
			Inshuju(&data, atoi(v));
			while (t > 0) {
				v[t] = 0;
				t--;
			}
			if (str[i] != ')') {
				i--;
				Infuhao(&symbol, '(');
			}
		}
		else if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
			while (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
				v[t] = str[i];
				t++;
				i++;
			}
			Inshuju(&data, atof(v));
			while (t > 0) {
				v[t] = 0;
				t--;
			}
			i--;
		}
		else {
			if (symbol.top == -1) {  
				Infuhao(&symbol, str[i]);
			}
			else if (judge(str[i]) == 1) { 
				Infuhao(&symbol, str[i]);
			}
			else if (judge(str[i]) == 2) {
				if (judge(Randfuhao(&symbol)) == 1) {
					Infuhao(&symbol, str[i]);
				}
				else if (judge(Randfuhao(&symbol)) == 2) { 
					while (symbol.top >= 0 && data.top >= 1) { 
						v2 = Putshuju(&data);
						v1 = Putshuju(&data);
						sum = Math(v1, v2, Putfuhao(&symbol));
						Inshuju(&data, sum);
					}
					Infuhao(&symbol, str[i]); 
				}
				else if (judge(Randfuhao(&symbol)) == 3) { 
					while (symbol.top >= 0 && data.top >= 1) { 
						v2 = Putshuju(&data);
						v1 = Putshuju(&data);
						sum = Math(v1, v2, Putfuhao(&symbol));
						Inshuju(&data, sum);
					}
					Infuhao(&symbol, str[i]);
				}
			}
			else if (judge(str[i]) == 3) { 
				if (judge(Randfuhao(&symbol)) == 1) {
					Infuhao(&symbol, str[i]);
				}
				else if (judge(Randfuhao(&symbol)) == 2) {
					Infuhao(&symbol, str[i]); 
				}
				else if (judge(Randfuhao(&symbol)) == 3) {
					while (symbol.top >= 0 && data.top >= 1) {
						v2 = Putshuju(&data);
						v1 = Putshuju(&data);
						sum = Math(v1, v2, Putfuhao(&symbol));
						Inshuju(&data, sum);
					}
					Infuhao(&symbol, str[i]);
				}
			}
			else if (judge(str[i]) == 4) {
				do {
					v2 = Putshuju(&data);
					v1 = Putshuju(&data);
					sum = Math(v1, v2, Putfuhao(&symbol));
					Inshuju(&data, sum);
				} while (judge(Randfuhao(&symbol)) != 1);
				Putfuhao(&symbol);
			}
		}
	}
	free(str);
	while (symbol.top != -1) {
		v2 = Putshuju(&data);
		v1 = Putshuju(&data);
		sum = Math(v1, v2, Putfuhao(&symbol));
		Inshuju(&data, sum);
	}

	return data.data[0];
}

int fPg_func(){//fx^gx
	float max = 0.0, min = 0.0;
	double func_sum1, func_sum2 = 0;
	double j1, j2;

	printf("请输入f(x)\n");
	char d;
	int i = 0;
	char _str1[200];
	while ((d = getchar()) != '\n') {
		_str1[i] = d;
		i++;
	}
	_str1[i] = '\0';

	while ((d = getchar()) != '\n' && (d = getchar()) != EOF);

	printf("请输入g(x)\n");
	i = 0;
	char _str2[200];
	while ((d = getchar()) != '\n') {
		_str2[i] = d;
		i++;
	}
	_str2[i] = '\0';



	printf("请输入定积分上界\n");
	scanf_s("%f", &max);

	printf("请输入定积分下界\n");
	scanf_s("%f", &min);

	char _str3[200];
	char _str4[200];

	int ci = 0;
	for (ci = 0; _str1[ci] != '\0'; ci++) {
		_str3[ci] = _str1[ci];
	}
	_str3[ci] = '\0';

	for (ci = 0; _str2[ci] != '\0'; ci++) {
		_str4[ci] = _str2[ci];
	}
	_str4[ci] = '\0';

	int j;
	int _j;
	char str[10] = { 0,0,0,0,0,0,0,0,0,0 };
	char str3[200];
	for (double i = min; i < max; i = i + dx) {

		for (ci = 0; _str3[ci] != '\0'; ci++) {
			_str1[ci] = _str3[ci];
		}
		_str1[ci] = '\0';

		for (ci = 0; _str4[ci] != '\0'; ci++) {
			_str2[ci] = _str4[ci];
		}
		_str2[ci] = '\0';

		j = 0;
		sprintf_s(str, "%f", i);
		while (str[j] != '\0') {
			j++;
		}
		str[j] = 0;
		j = 0;
		_j = 0;

		while (_str1[j] != '\0') {
			if (_str1[j] == 'x') {
				int k = 0;
				for (; _str1[k] != '\0'; k++) {
					str3[k] = _str1[k];
				}
				str3[k] = '\0';
				k = 0;
				for (; k < 8; k++) {
					_str1[j + k] = str[k];
				}
				for (_j = j + 1; str3[_j] != '\0'; _j++) {
					_str1[_j + k - 1] = str3[_j];
				}
				_str1[_j + k - 1] = '\0';
			}
			j++;
		}
		j1 = pnc(_str1);
		
		j = 0;
		_j = 0;

		while (_str2[j] != '\0') {
			if (_str2[j] == 'x') {
				int k = 0;
				for (; _str2[k] != '\0'; k++) {
					str3[k] = _str2[k];
				}
				str3[k] = '\0';
				k = 0;
				for (; k < 8; k++) {
					_str2[j + k] = str[k];
				}
				for (_j = j + 1; str3[_j] != '\0'; _j++) {
					_str2[_j + k - 1] = str3[_j];
				}
				_str2[_j + k - 1] = '\0';
			}
			j++;
		}
		j2 = pnc(_str2);

		func_sum1 = pow(j1, j2);
		func_sum2 = func_sum2 + func_sum1 * dx;
	}

	printf("%f",func_sum2);
	return 0;
}

int sinf_func() {//sinfx
	float max = 0.0, min = 0.0;
	double func_sum1, func_sum2 = 0;
	double j1, j2;

	printf("请输入f(x)\n");
	char d;
	int i = 0;
	char _str1[200];
	while ((d = getchar()) != '\n') {
		_str1[i] = d;
		i++;
	}
	_str1[i] = '\0';

	while ((d = getchar()) != '\n' && (d = getchar()) != EOF);

	printf("请输入定积分上界\n");
	scanf_s("%f", &max);

	printf("请输入定积分下界\n");
	scanf_s("%f", &min);

	char _str3[200];

	int ci = 0;
	for (ci = 0; _str1[ci] != '\0'; ci++) {
		_str3[ci] = _str1[ci];
	}
	_str3[ci] = '\0';

	int j;
	int _j;
	char str[10] = { 0,0,0,0,0,0,0,0,0,0 };
	char str3[200];
	for (double i = min; i < max; i = i + dx) {

		for (ci = 0; _str3[ci] != '\0'; ci++) {
			_str1[ci] = _str3[ci];
		}
		_str1[ci] = '\0';

		j = 0;
		sprintf_s(str, "%f", i);
		while (str[j] != '\0') {
			j++;
		}
		str[j] = 0;
		j = 0;
		_j = 0;

		while (_str1[j] != '\0') {
			if (_str1[j] == 'x') {
				int k = 0;
				for (; _str1[k] != '\0'; k++) {
					str3[k] = _str1[k];
				}
				str3[k] = '\0';
				k = 0;
				for (; k < 8; k++) {
					_str1[j + k] = str[k];
				}
				for (_j = j + 1; str3[_j] != '\0'; _j++) {
					_str1[_j + k - 1] = str3[_j];
				}
				_str1[_j + k - 1] = '\0';
			}
			j++;
		}
		j1 = pnc(_str1);

		func_sum1 = sin(j1);
		func_sum2 = func_sum2 + func_sum1 * dx;
	}

	printf("%f", func_sum2);
	return 0;
}

int fLg_func() {//lnfx/lngx
	float max = 0.0, min = 0.0;
	double func_sum1, func_sum2 = 0;
	double j1, j2;

	printf("请输入f(x)\n");
	char d;
	int i = 0;
	char _str1[200];
	while ((d = getchar()) != '\n') {
		_str1[i] = d;
		i++;
	}
	_str1[i] = '\0';

	while ((d = getchar()) != '\n' && (d = getchar()) != EOF);

	printf("请输入g(x)\n");
	i = 0;
	char _str2[200];
	while ((d = getchar()) != '\n') {
		_str2[i] = d;
		i++;
	}
	_str2[i] = '\0';



	printf("请输入定积分上界\n");
	scanf_s("%f", &max);

	printf("请输入定积分下界\n");
	scanf_s("%f", &min);

	char _str3[200];
	char _str4[200];

	int ci = 0;
	for (ci = 0; _str1[ci] != '\0'; ci++) {
		_str3[ci] = _str1[ci];
	}
	_str3[ci] = '\0';

	for (ci = 0; _str2[ci] != '\0'; ci++) {
		_str4[ci] = _str2[ci];
	}
	_str4[ci] = '\0';

	int j;
	int _j;
	char str[10] = { 0,0,0,0,0,0,0,0,0,0 };
	char str3[200];
	for (double i = min; i < max; i = i + dx) {

		for (ci = 0; _str3[ci] != '\0'; ci++) {
			_str1[ci] = _str3[ci];
		}
		_str1[ci] = '\0';

		for (ci = 0; _str4[ci] != '\0'; ci++) {
			_str2[ci] = _str4[ci];
		}
		_str2[ci] = '\0';

		j = 0;
		sprintf_s(str, "%f", i);
		while (str[j] != '\0') {
			j++;
		}
		str[j] = 0;
		j = 0;
		_j = 0;

		while (_str1[j] != '\0') {
			if (_str1[j] == 'x') {
				int k = 0;
				for (; _str1[k] != '\0'; k++) {
					str3[k] = _str1[k];
				}
				str3[k] = '\0';
				k = 0;
				for (; k < 8; k++) {
					_str1[j + k] = str[k];
				}
				for (_j = j + 1; str3[_j] != '\0'; _j++) {
					_str1[_j + k - 1] = str3[_j];
				}
				_str1[_j + k - 1] = '\0';
			}
			j++;
		}
		j1 = pnc(_str1);

		j = 0;
		_j = 0;

		while (_str2[j] != '\0') {
			if (_str2[j] == 'x') {
				int k = 0;
				for (; _str2[k] != '\0'; k++) {
					str3[k] = _str2[k];
				}
				str3[k] = '\0';
				k = 0;
				for (; k < 8; k++) {
					_str2[j + k] = str[k];
				}
				for (_j = j + 1; str3[_j] != '\0'; _j++) {
					_str2[_j + k - 1] = str3[_j];
				}
				_str2[_j + k - 1] = '\0';
			}
			j++;
		}
		j2 = pnc(_str2);

		func_sum1 = log(j1) / log(j2);
		func_sum2 = func_sum2 + func_sum1 * dx;
	}

	printf("%f", func_sum2);
	return 0;
}

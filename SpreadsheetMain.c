#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SPREADSHEET_LIMIT 10
#define SPREADSHEET_NUM_LIMIT 50
#define ALPHA_GRID "  |  A  |  B  |  C  |  D  |  E  |  F  |  G  |  H  |  I  |  J  |\n"
enum alpha_value {A=0, B, C, D, E, F, G, H, I, J};

typedef struct cell{
	enum alpha_value cell_alpha;
	char *cell_alpha_str;
	int cell_pos;
	float cell_value;
} spreadsheet_cell;

spreadsheet_cell spreadsheet[SPREADSHEET_LIMIT][SPREADSHEET_NUM_LIMIT]; //Spreadsheet values.
FILE *spreadsheet_fp;
FILE *program_fp;

void cellcharToAlpha (spreadsheet_cell *cell) {
	if(strcmp(cell->cell_alpha_str, "A") == 0 || strcmp((*cell).cell_alpha_str, "a") == 0)
		(*cell).cell_alpha = A;
	else if(strcmp((*cell).cell_alpha_str, "B") == 0 || strcmp((*cell).cell_alpha_str, "b") == 0)
		(*cell).cell_alpha = B;
	else if(strcmp((*cell).cell_alpha_str, "C") == 0 || strcmp((*cell).cell_alpha_str, "c") == 0)
		(*cell).cell_alpha = C;
	else if(strcmp((*cell).cell_alpha_str, "D") == 0 || strcmp((*cell).cell_alpha_str, "d") == 0)
		(*cell).cell_alpha = D;
	else if(strcmp((*cell).cell_alpha_str, "E") == 0 || strcmp((*cell).cell_alpha_str, "e") == 0)
		(*cell).cell_alpha = E;
	else if(strcmp((*cell).cell_alpha_str, "F") == 0 || strcmp((*cell).cell_alpha_str, "f") == 0)
		(*cell).cell_alpha = F;
	else if(strcmp((*cell).cell_alpha_str, "G") == 0 || strcmp((*cell).cell_alpha_str, "g") == 0)
		(*cell).cell_alpha = G;
	else if(strcmp((*cell).cell_alpha_str, "H") == 0 || strcmp((*cell).cell_alpha_str, "h") == 0)
		(*cell).cell_alpha = H;
	else if(strcmp((*cell).cell_alpha_str, "I") == 0 || strcmp((*cell).cell_alpha_str, "i") == 0)
		(*cell).cell_alpha = I;
	else if(strcmp((*cell).cell_alpha_str, "J") == 0 || strcmp((*cell).cell_alpha_str, "j") == 0)
		(*cell).cell_alpha = J;
	return;
}

void display_spreadsheet (void) { 
	enum alpha_value f;
	int fl;
	printf(ALPHA_GRID);
	for(fl = 0; fl < SPREADSHEET_NUM_LIMIT; fl++) {
		printf("%2d", fl);
		for(f = A; f < SPREADSHEET_LIMIT; f++) {
			if(spreadsheet[f][fl].cell_value != 0)
				printf("|%.2f", spreadsheet[f][fl].cell_value);
			else 
				printf("|     ");
		}
		putchar('|');
		putchar('\n');
	}	
	putchar('\n');
}

void spreadsheet_init (void) {
	enum alpha_value f;
	int fl;
	printf("Keep your data organized in style, without complicated instructions.\n");
	printf("Text Spreadsheets, for those who value convenience.\n\n");
	for(f = A; f < SPREADSHEET_LIMIT; f++) {
		for(fl = 0; fl < SPREADSHEET_NUM_LIMIT; fl++) {
			spreadsheet[f][fl].cell_value = 0.00;
		}
	}
	display_spreadsheet ();
}

void resetSpreadsheetAll (void) {
	enum alpha_value f;
	int fl;
	for(f = A; f < SPREADSHEET_LIMIT; f++) {
		for(fl = 0; fl < SPREADSHEET_NUM_LIMIT; fl++) {
			spreadsheet[f][fl].cell_value = 0;
		}
	}
}

spreadsheet_cell clearSpreadsheetCell (enum alpha_value alpha, int nPos) {
	spreadsheet_cell popCell;
 
	popCell = spreadsheet[alpha][nPos];
	spreadsheet[alpha][nPos].cell_value = 0.00;

	return (popCell);
}

int processKeywordPrompt (char *keyword) {
	spreadsheet_cell info_stream, operator1, operator2;
    char istring[3], op1string[3], op2string[3], fstring[32], function[16];
	float results = 0;
	sprintf(op1string, "\0");
	sprintf(op2string, "\0");
	sprintf(istring, "\0");
	sprintf(fstring, "\0");
	info_stream.cell_alpha_str = istring;
	operator1.cell_alpha_str = op1string;
	operator2.cell_alpha_str = op2string;
	if(strcmp(keyword, "enter") == 0) {
		scanf(" %s = %f", info_stream.cell_alpha_str, &info_stream.cell_value);  
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value = info_stream.cell_value;
		display_spreadsheet ();
	}
	else if(strcmp(keyword, "access") == 0) {
		scanf(" %s", info_stream.cell_alpha_str);
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		printf("Value: %f\n", spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value);
	}
	else if(strcmp(keyword, "clear") == 0) {
		scanf(" %s", info_stream.cell_alpha_str);
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		clearSpreadsheetCell (info_stream.cell_alpha, info_stream.cell_pos);
		display_spreadsheet ();
	}
	else if(strcmp(keyword, "function") == 0) {
		scanf(" %s %s %s %s", function, info_stream.cell_alpha_str, operator2.cell_alpha_str, operator1.cell_alpha_str);	
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		operator2.cell_pos = strtol(operator2.cell_alpha_str, &operator2.cell_alpha_str, 10); 
		operator1.cell_pos = strtol(operator1.cell_alpha_str, &operator1.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		cellcharToAlpha(&operator2);
		cellcharToAlpha(&operator1);
		if(strcmp(function, "sum") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value + spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "subtract") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value - spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "multiply") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value * spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "divide") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value / spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "power") == 0) 
			results = pow((int)spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value, (int)spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value);
		else if(strcmp(function, "sqrt") == 0) 
			results = sqrtf(spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value);

		spreadsheet[operator1.cell_alpha][operator1.cell_pos].cell_value = results;
		display_spreadsheet();
	}
	else if(strcmp(keyword, "save") == 0) {
		scanf(" %s", fstring);
		spreadsheet_fp = fopen(fstring, "w+");
		for(int i1 = 0; i1 < SPREADSHEET_LIMIT; i1++) {
			for(int i2 = 0; i2 < SPREADSHEET_NUM_LIMIT; i2++) {
				fprintf(spreadsheet_fp, "%f ", spreadsheet[i1][i2].cell_value);
			}
			fprintf(spreadsheet_fp, "\n");
		}
		fclose(spreadsheet_fp);
	}
	else if(strcmp(keyword, "upload") == 0) {
		scanf(" %s", fstring);
		spreadsheet_fp = fopen(fstring, "r+");
		for(int i1 = 0; i1 < SPREADSHEET_LIMIT; i1++) {
			for(int i2 = 0; i2 < SPREADSHEET_NUM_LIMIT; i2++) {
				fscanf(spreadsheet_fp, "%f", &spreadsheet[i1][i2].cell_value);
			}
		}
		fclose(spreadsheet_fp);	
		printf("\n");	
		display_spreadsheet();
	}
	else if(strcmp(keyword, "EXIT") == 0) {
		return(0);
	}
	else {
		printf(">>ERROR: Unrecognized Action Description\n");
		return(1);
	}
}

int processKeywordPromptPRG(char *keyword, FILE *fp) {
	spreadsheet_cell info_stream, operator1, operator2;
    char istring[3], op1string[3], op2string[3], fstring[32], function[16];
	float results = 0;
	sprintf(op1string, "\0");
	sprintf(op2string, "\0");
	sprintf(istring, "\0");
	sprintf(fstring, "\0");
	info_stream.cell_alpha_str = istring;
	operator1.cell_alpha_str = op1string;
	operator2.cell_alpha_str = op2string;
	if(strcmp(keyword, "enter") == 0) {
		fscanf(fp, " %s = %f", info_stream.cell_alpha_str, &info_stream.cell_value);  
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value = info_stream.cell_value;
		display_spreadsheet ();
	}
	else if(strcmp(keyword, "access") == 0) { 
		fscanf(fp, " %s", info_stream.cell_alpha_str);
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		printf("Value: %f\n", spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value);
	}
	else if(strcmp(keyword, "clear") == 0) {
		fscanf(fp, " %s", info_stream.cell_alpha_str);
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		clearSpreadsheetCell (info_stream.cell_alpha, info_stream.cell_pos);
		display_spreadsheet ();
	}
	else if(strcmp(keyword, "function") == 0) {
		fscanf(fp, " %s %s %s %s", function, info_stream.cell_alpha_str, operator2.cell_alpha_str, operator1.cell_alpha_str);	
		info_stream.cell_pos = strtol(info_stream.cell_alpha_str, &info_stream.cell_alpha_str, 10); 
		operator2.cell_pos = strtol(operator2.cell_alpha_str, &operator2.cell_alpha_str, 10); 
		operator1.cell_pos = strtol(operator1.cell_alpha_str, &operator1.cell_alpha_str, 10); 
		cellcharToAlpha(&info_stream);
		cellcharToAlpha(&operator2);
		cellcharToAlpha(&operator1);
		if(strcmp(function, "sum") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value + spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "subtract") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value - spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "multiply") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value * spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "divide") == 0)
			results = spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value / spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value;
		else if(strcmp(function, "power") == 0) 
			results = pow((int)spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value, (int)spreadsheet[operator2.cell_alpha][operator2.cell_pos].cell_value);
		else if(strcmp(function, "sqrt") == 0) 
			results = sqrtf(spreadsheet[info_stream.cell_alpha][info_stream.cell_pos].cell_value);

		spreadsheet[operator1.cell_alpha][operator1.cell_pos].cell_value = results;
		display_spreadsheet();
	}
	else if(strcmp(keyword, "save") == 0) {
		scanf(" %s", fstring);
		spreadsheet_fp = fopen(fstring, "w+");
		for(int i1 = 0; i1 < SPREADSHEET_LIMIT; i1++) {
			for(int i2 = 0; i2 < SPREADSHEET_NUM_LIMIT; i2++) {
				fprintf(spreadsheet_fp, "%f ", spreadsheet[i1][i2].cell_value);
			}
			fprintf(spreadsheet_fp, "\n");
		}
		fclose(spreadsheet_fp);
	}
	else if(strcmp(keyword, "upload") == 0) {
		scanf(" %s", fstring);
		spreadsheet_fp = fopen(fstring, "r+");
		for(int i1 = 0; i1 < SPREADSHEET_LIMIT; i1++) {
			for(int i2 = 0; i2 < SPREADSHEET_NUM_LIMIT; i2++) {
				fscanf(spreadsheet_fp, "%f", &spreadsheet[i1][i2].cell_value);
			}
		}
		fclose(spreadsheet_fp);	
		printf("\n");	
		display_spreadsheet();
	}
	else if(strcmp(keyword, "EXIT") == 0) {
		return(0);
	}
	else {
		printf(">>ERROR: Unrecognized Action Description\n");
		return (1);
	}
}

int main (void) 
{
	char prompt_stream[16], file_name[32], mode;
	int program_size = 0;
	int msg = 1;
	while(1) {
		mode = '\0';
		printf("Mode (Program/Free Input): ");
		scanf("%c", &mode);
		if(mode == 'F' || mode == 'f') {
			spreadsheet_init ();
			while(1) {
				 printf("Describe Action: ");
				 scanf(" %s", prompt_stream);
				 msg = processKeywordPrompt(prompt_stream);
				 printf("\n\n");
				if(msg == 0) 
					return (0);
			}
		}
		else if(mode == 'P' || mode == 'p') {
			printf("Program file: ");
			scanf(" %s", file_name);
			program_fp = fopen(file_name, "r+");
			fscanf(program_fp, "%d", &program_size);
			for(int count = 0; count < program_size; count++) {
				fscanf(program_fp, " %s", prompt_stream);
				msg = processKeywordPromptPRG(prompt_stream, program_fp);
				if(msg == 0) 
					return (0);
			}
		}
	}
	return (0);
}

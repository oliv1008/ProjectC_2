#include <stdio.h>
#include "include/parser.h"

int main(int argc, char **argv)
{
	char c;
	
	FILE * f = fopen("/home/olivier/Bureau/Polytech/ProjetC_2/MKP-Instances/_mknapcb1_res.txt", "r");
	Parser(f);
	
	//Solution temp pour empêcher le terminal de se fermer
	scanf("%c", &c);
	return 0;
}

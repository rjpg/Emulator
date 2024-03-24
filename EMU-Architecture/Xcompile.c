#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
char label[10];
short int instru,arg1,arg2,arg3;
char arg_caso_jal[10];
}INS_LINE;

FILE *in,*out;

INS_LINE PRE_PROGRAM[65536];

int lastc=0;
char lastI[5];
int lastR;
int lastN;
char lastL[10];


int PC=0;

void get_spaces (void)
{
        while ((lastc=fgetc(in))==' '|| lastc=='\n' );
}


void get_instruction(void)
{
        int i;
        lastI[0]=lastc;
        i=fgetc(in);
        if (i==' '|| i==EOF || i=='\n')
                {lastI[1]='\0';
                return;} else lastI[1]=i;
        i=fgetc(in);
        if (i==' '|| i==EOF || i=='\n')
                {lastI[2]='\0';
                return;} else lastI[2]=i;
        i=fgetc(in);
        if (i==' '|| i==EOF || i=='\n')
                {lastI[3]='\0';
                return;} else lastI[3]=i;
        i=fgetc(in);
        if (i==' '|| i==EOF || i=='\n')
                {lastI[4]='\0';
                return;} else lastI[4]=i;
}


void get_register (void)
{
        if (lastc!='R')
                {
                printf ("ERROR :expeting register...[INST:%d]\n",PC);
                exit (1);
                }
        if (!fscanf(in,"%d",&lastR))
                {
                printf ("ERROR :Reading register...[INST:%d]\n",PC);
                exit (1);
                }
}


void get_number (void)
{

        int i=1;
        char n[11];
        n[0]=lastc;
        while (lastc!=' '&& lastc!=EOF && lastc!='\n')
        {        lastc=fgetc(in);
                n[i++]=lastc;
                }
        if(!sscanf(n,"%d",&lastN))
                {
                printf ("ERROR :Reading register...[INST:%d]\n",PC);
                exit (1);
                }

}


void get_label (void)
{
        int i=0;
        char n[10];

        if (lastc!=':')
                {
                printf ("ERROR :expeting label...[INST:%d]\n",PC);
                exit (1);
                }

        while (lastc!=' '&& lastc!=EOF && lastc!='\n')
        {        lastc=fgetc(in);
                n[i++]=lastc;
                }
        n[i-1]='\n';
        sscanf(n,"%s",&lastL);

}

int fill_pre_prog (char inst[5])
{
//        printf ("%s\n",inst);
//        printf("%d",strlen(inst));
        if (inst[0]=='\0') printf("ERRRRO!!");

        if (strcmp(inst,"NOP")==0)
                {
                PRE_PROGRAM[PC].instru=0x0000;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;
                return 0;
                }

        if (strcmp(inst,"ADD")==0)
                {
                PRE_PROGRAM[PC].instru=0x0001;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SUB")==0)
                {
                PRE_PROGRAM[PC].instru=0x0002;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"MUL")==0)
                {
                PRE_PROGRAM[PC].instru=0x0003;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"DIV")==0)
                {
                PRE_PROGRAM[PC].instru=0x0004;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"NOT")==0)
                {
                PRE_PROGRAM[PC].instru=0x0005;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }

        if (strcmp(inst,"AND")==0)
                {
                PRE_PROGRAM[PC].instru=0x0006;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"OR")==0)
                {
                PRE_PROGRAM[PC].instru=0x0007;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SL")==0)
                {
                PRE_PROGRAM[PC].instru=0x0008;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }


        if (strcmp(inst,"SR")==0)
                {
                PRE_PROGRAM[PC].instru=0x0009;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"LW")==0)
                {
                PRE_PROGRAM[PC].instru=0x000A;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"SW")==0)
                {
                PRE_PROGRAM[PC].instru=0x000B;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"J")==0)
                {
                PRE_PROGRAM[PC].instru=0x000C;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }


        if (strcmp(inst,"JR")==0)
                {
                PRE_PROGRAM[PC].instru=0x000D;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }

        if (strcmp(inst,"BR")==0)
                {
                PRE_PROGRAM[PC].instru=0x000E;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"BEQ")==0)
                {
                PRE_PROGRAM[PC].instru=0x000F;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }


        if (strcmp(inst,"BNE")==0)
                {
                PRE_PROGRAM[PC].instru=0x0010;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"BGT")==0)
                {
                PRE_PROGRAM[PC].instru=0x0011;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"BGE")==0)
                {
                PRE_PROGRAM[PC].instru=0x0012;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"BLT")==0)
                {
                PRE_PROGRAM[PC].instru=0x0013;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"BLE")==0)
                {
                PRE_PROGRAM[PC].instru=0x0014;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }


        if (strcmp(inst,"SEQ")==0)
                {
                PRE_PROGRAM[PC].instru=0x00015;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SNE")==0)
                {
                PRE_PROGRAM[PC].instru=0x00016;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SGT")==0)
                {
                PRE_PROGRAM[PC].instru=0x00017;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SGE")==0)
                {
                PRE_PROGRAM[PC].instru=0x00018;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SLT")==0)
                {
                PRE_PROGRAM[PC].instru=0x00019;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SLE")==0)
                {
                PRE_PROGRAM[PC].instru=0x0001A;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"ADDI")==0)
                {
                PRE_PROGRAM[PC].instru=0x001B;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;

                return 0;
                }

        if (strcmp(inst,"CSET")==0)
                {
                PRE_PROGRAM[PC].instru=0x0001C;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg3=(lastR-1);

                return 0;
                }

        if (strcmp(inst,"SYS")==0)
                {
                PRE_PROGRAM[PC].instru=0x0001D;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                get_spaces();
                get_number();
                PRE_PROGRAM[PC].arg3=lastN;
                switch (lastN)
                        {
                        case 2 :
                                get_spaces();
                                get_register();
                                PRE_PROGRAM[PC].arg1=(lastR-1);
                                break;
                        case 3 :
                                get_spaces();
                                get_register();
                                PRE_PROGRAM[PC].arg1=(lastR-1);
                                break;


                        case 4 :
                                get_spaces();
                                get_register();
                                PRE_PROGRAM[PC].arg1=(lastR-1);
                                break;

                        case 5 :
                                get_spaces();
                                get_register();
                                PRE_PROGRAM[PC].arg1=(lastR-1);
                                break;

                        }

                return 0;
                }

        if (strcmp(inst,"PUS")==0)
                {
                PRE_PROGRAM[PC].instru=0x001E;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }

        if (strcmp(inst,"POP")==0)
                {
                PRE_PROGRAM[PC].instru=0x001F;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }


        if (strcmp(inst,"PUA")==0)
                {
                PRE_PROGRAM[PC].instru=0x0020;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }

        if (strcmp(inst,"POA")==0)
                {
                PRE_PROGRAM[PC].instru=0x0021;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }

        if (strcmp(inst,"PUC")==0)
                {
                PRE_PROGRAM[PC].instru=0x0022;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }

        if (strcmp(inst,"POC")==0)
                {
                PRE_PROGRAM[PC].instru=0x0023;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;

                return 0;
                }



/* 
                case 0x00 : break; //nop
                case 0x01 : add (inst>>8); break;
                case 0x02 : sub (inst>>8);break;
                case 0x03 : mul (inst>>8);break;
                case 0x04 : div (inst>>8);break;
                case 0x05 : not (inst>>8); break;
                case 0x06 : and (inst>>8);break;
                case 0x07 : or (inst>>8);break;
                case 0x08 : sl (inst>>8);break;
                case 0x09 : sr (inst>>8);break;
                case 0x0A : lw (inst>>8);break;
                case 0x0B : sw (inst>>8);break;
                case 0x0C : j (inst>>8);break;
                case 0x0D : jr (inst>>8);break;
                case 0x0E : br (inst>>8);break;
                case 0x0F : beq (inst>>8);break;
                case 0x10 : bne (inst>>8);break;
                case 0x11 : bgt (inst>>8);break;
                case 0x12 : bge (inst>>8);break;
                case 0x13 : blt (inst>>8);break;
                case 0x14 : ble (inst>>8);break;
                case 0x15 : seq (inst>>8);break;
                case 0x16 : sne (inst>>8);break;
                case 0x17 : sgt (inst>>8);break;
                case 0x18 : sge (inst>>8);break;
                case 0x19 : slt (inst>>8);break;
                case 0x1A : sle (inst>>8);break;
                case 0x1B : addi (inst>>8);break;
                case 0x1C : cset (inst>>8);break;
                case 0x1D : sys (inst>>8);break;
                case 0x1E : pus (inst>>8);break;
                case 0x1F : pop (inst>>8);break;
                case 0x20 : pua ();break;
                case 0x21 : poa ();break;
                case 0x22 : puc ();break;
                case 0x23 : poc ();break;
*/

        if (strcmp(inst,"JAL")==0)
                {
                PRE_PROGRAM[PC].instru=0x0024;
                PRE_PROGRAM[PC].arg1=0;
                PRE_PROGRAM[PC].arg2=0;
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }


        if (strcmp(inst,"JEQ")==0)
                {
                PRE_PROGRAM[PC].instru=0x0025;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }

        if (strcmp(inst,"JNE")==0)
                {
                PRE_PROGRAM[PC].instru=0x0026;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }

        if (strcmp(inst,"JGT")==0)
                {
                PRE_PROGRAM[PC].instru=0x0027;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }

        if (strcmp(inst,"JGE")==0)
                {
                PRE_PROGRAM[PC].instru=0x0028;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }

        if (strcmp(inst,"JLT")==0)
                {
                PRE_PROGRAM[PC].instru=0x0029;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }


        if (strcmp(inst,"JLE")==0)
                {
                PRE_PROGRAM[PC].instru=0x002A;
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg1=(lastR-1);
                get_spaces();
                get_register();
                PRE_PROGRAM[PC].arg2=(lastR-1);
                PRE_PROGRAM[PC].arg3=0;
                get_spaces();
                get_label();
                strcpy(PRE_PROGRAM[PC].arg_caso_jal,lastL);

                return 0;
                }
        printf ("ERROR :Unknone menemonic...[INST:%d]\n",PC);
        exit(1);
        return 0;
}

int pos_label(char l[10])
{
        int i;
        for (i=1;i<PC;i++)
                if(strcmp(l,PRE_PROGRAM[i].label)==0)
                        return i;
        return -1;
}

void transform(void)
{
        int i,x,h;
        for (i=0;i<PC;i++)
                {
                if (PRE_PROGRAM[i].instru==0x0024)
                        {
                        if((x=pos_label(PRE_PROGRAM[i].arg_caso_jal))==-1)
                                {printf("ERROR : Label not found...[:%s]\n",PRE_PROGRAM[i].arg_caso_jal);
                                 exit (1);}
                        PRE_PROGRAM[i].instru=0x000C;
                        PRE_PROGRAM[i].arg3=x;
                 //       printf("label:%s\n",PRE_PROGRAM[i].arg_caso_jal);
                 //       printf("%d\n",x);
                        }
                for (h=0;h<6;h++)
                if (PRE_PROGRAM[i].instru==0x0025+h)
                        {
                        if((x=pos_label(PRE_PROGRAM[i].arg_caso_jal))==-1)
                                {printf("ERROR : Label not found...[:%s]\n",PRE_PROGRAM[i].arg_caso_jal);
                                 exit (1);}
                        PRE_PROGRAM[i].instru=0x000F+h;
                        PRE_PROGRAM[i].arg3=x;
                 //       printf("label:%s\n",PRE_PROGRAM[i].arg_caso_jal);
                 //       printf("%d\n",x);
                        }



                 }
}
            
void make_output (void)
{
        int i,aux,aux2,aux3,ins;
        
        for (i=0;i<PC;i++)
                 {
                 aux=(PRE_PROGRAM[i].arg3<<16);
                 aux2=(PRE_PROGRAM[i].arg2<<12);
                 aux3=(PRE_PROGRAM[i].arg1<<8);
                 ins= aux | aux2;
                 ins= ins | aux3;
                 ins= ins | PRE_PROGRAM[i].instru;
                 fprintf (out , "%X\n",ins);
                 }

        
}

int main (int argc,char *argv[])
{
        int i;

        printf ("\n(c) X-prog 2000  (Trabalho de A.C.) Assemblador\n");
        if (argc!=3)
                {
                printf ("\nNedeed 2 arguments\n");
                printf ("Sintaxe: Xcompile [file in] [file out]\n");
                printf ("EX:      Xcompile teste.asx teste.xsm\n\n");
                return 1;
                }

        printf("Input file: %s",argv[1]);
        printf("    Output file: %s\n\n",argv[2]);

        if ((in = fopen(argv[1], "rt"))== NULL)
        {
                printf("Cannot open input file.\n");
                return 1;
        }


        //fill_pre_prog ("JAL");
        PRE_PROGRAM[PC].instru=0x0024;
        strcpy(PRE_PROGRAM[PC].arg_caso_jal,"START");
        PC++;

        get_spaces();
        while (lastc!=EOF)
        {
        
        if (lastc==':')
                {
                get_label();
                strcpy (PRE_PROGRAM[PC].label,lastL);
                get_spaces();
                get_instruction();
                fill_pre_prog (lastI);
                }
        else
                {
                get_instruction();
                fill_pre_prog (lastI);
                }
                PC++;
        get_spaces();
        }

        

        transform();   //transforma o jumps 

        for (i=0;i<PC;i++)
                printf ("pc:%d , label:%s , inst:%X a1:%d a2:%d a3:%d\n",
                i,PRE_PROGRAM[i].label,PRE_PROGRAM[i].instru,PRE_PROGRAM[i].arg1,
                PRE_PROGRAM[i].arg2,PRE_PROGRAM[i].arg3);

        if ((out = fopen(argv[2], "w+")) == NULL)
        {
                printf("Cannot open output file.\n");
                return 1;
        } 


        make_output ();
/*        printf("label jal: %s\n",PRE_PROGRAM[6].arg_caso_jal);
        if (strcmp(PRE_PROGRAM[2].label,PRE_PROGRAM[6].arg_caso_jal)==0)
                printf("igual a pr2 !!! FIXE!");                        */
        fclose (in);
        fclose (out);

        return 0;
}

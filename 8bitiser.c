

#include<stdio.h>
#include<stdlib.h> 
#include<time.h> // Implements srand()
#include<string.h> // Implements strcpy()/strcmp()


// List of recognized notes for the 8_BITIZER
#define DO 523
#define REB 554
#define RE 587
#define RED 622
#define MI 659
#define FA 698
#define FAD 740
#define SOL 784
#define SOLD 831
#define LA 880
#define LAD 932
#define SI 988
#define DOA 1046
#define SIG 494
#define SIBG 466
#define LAG 440
#define SOLDG 415
#define SOLG 392

#define MAXIMUM_LENGHT 20


//-------Fonctions-----------  
int choixModePlay();
int choixMode();
char* InputHandler(char * MyString);
float swiftness ();
void reverse (FILE* LeDescripteur, float swiftness);
FILE* xfopen(char* LeFichier);
int detectFrequency(char* LaNote);
void NoteTimeChoice(char* sNote);
void play(char * sNote);
void playFile();
void readfile(FILE *LeDescripteur,float swiftness);
void Accueil();


int main()
{
  char* sNote = malloc(sizeof(char)*255);
  int LeChoixMode = NULL;

  Accueil();
  LeChoixMode = choixMode();
  if(LeChoixMode == 1)
    NoteTimeChoice(sNote);
  else
    {
      playFile();
    }
  free(sNote);
  return EXIT_SUCCESS;

}


//Random mode function, picks random note and random time and plays the associated sound.
void NoteTimeChoice(char* sNote)
{
  srand(time(NULL));
  int note = (rand()%17);            
  float noteTime = 0;
   while(1)
    {
      note = (rand()%17);
      do
	{
	  noteTime = (float)rand()/(float)RAND_MAX;
	}
      while(noteTime < 0.1 || noteTime > 0.4); 
	 

      switch(note)
      {
      case 0: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime,DO);
	break;

      case 1: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, REB);
	break;

      case 2: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, RE);
	break;

      case 3: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, RED);
	break;

      case 4: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, MI);
	break;

      case 5: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, FA);
	break;

      case 6: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, FAD);
	break;

      case 7: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SOL);
	break;

      case 8: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SOLD);
	break;

      case 9: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, LA);
	break;

      case 10: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, LAD);
	break;

      case 11: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SI);
	break;
	
	case 12: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, DOA);
	break;

      case 13: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SIG);
	break;

      case 14: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SIBG);
	break;

      case 15: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, LAG);
	break;

      case 16: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SOLDG);
	break;

      case 17: 
	sprintf(sNote,"sox -r 8000 -n output.au synth %f sine %d",noteTime, SOLG);
	break;

      default:
	  printf("erreur\n");
      }
      play(sNote);
    }
}

// Call to system command
void play(char * sNote)
{
  system(sNote);
  system("play output.au");
}

// PlayFile mode-- Main screen  //
void playFile()
{
  float vitesse = 1; 
  char *LeFichier = malloc(sizeof(char)*20);
  FILE *LeDescripteur=NULL;
  int playMode = NULL;
 
  printf("Quel fichier voulez vous jouer ?\n");
  InputHandler(LeFichier);
  LeDescripteur = xfopen(LeFichier);

  playMode = choixModePlay();
  if(playMode == 1)
    {
      vitesse = swiftness();
      readfile(LeDescripteur,vitesse);
    }
  else
    {
      vitesse = swiftness();
      reverse(LeDescripteur,vitesse);
    }
  free(LeFichier);
  fclose(LeDescripteur);
}

//safe implementation for fopen function
FILE* xfopen(char* LeFichier)
{
  FILE *tmp = fopen(LeFichier,"r");
  while(tmp == 0)
    {
      printf("Fichier introuvable, veuillez reessayer\n");
      scanf("%s", LeFichier);
      tmp = fopen(LeFichier,"r");
    }

  return tmp;
}


// readfile function reads caractere each by one, stores it in a grid, then call Play function.
void readfile(FILE *LeDescripteur, float swiftness)
{
  char LaNote[6];
  float LeTemps = 0.0;
  int LeSleep = 0;
  int LaNote2 = 0;
  char LaCommande[50];


  while(fgetc(LeDescripteur) != EOF)
    {
      fscanf(LeDescripteur,"%s %f %d\n",LaNote,&LeTemps,&LeSleep);
      LaNote2 = detectFrequency(LaNote);
      sprintf(LaCommande,"sox -r 8000 -n output.au synth %f sine %d", LeTemps*swiftness, LaNote2);
      play(LaCommande);
      //sleep(LeSleep);
    }
}

// figure out the note with the entry read from the file given by User
int detectFrequency(char* LaNote)
{

  if (strcmp(LaNote, "DO") == 0)
    return 523;
  else if (strcmp(LaNote, "SIG") == 0)
    return 494;
  else if (strcmp(LaNote, "SIBG") == 0)
    return 466;
  else if (strcmp(LaNote, "LAG") == 0)
    return 440;
  else if (strcmp(LaNote, "SOLDG") == 0)
    return 415;
  else if (strcmp(LaNote, "SOLG") == 0)
    return 392;
  else if (strcmp(LaNote, "REB") == 0)
    return 554;
  else if (strcmp(LaNote, "RE") == 0)
    return 587;
  else if (strcmp(LaNote, "RED") == 0)
    return 662;
  else if (strcmp(LaNote, "MI") == 0)
    return 659;
  else if (strcmp(LaNote, "FA") == 0)
    return 698;
  else if (strcmp(LaNote, "FAD") == 0)
    return 740;
  else if (strcmp(LaNote, "SOL") == 0)
    return 784;
  else if (strcmp(LaNote, "SOLD") == 0)
    return 831;
  else if (strcmp(LaNote, "LA") == 0)
    return 880;
  else if (strcmp(LaNote, "LAD") == 0)
    return 932;
  else if (strcmp(LaNote, "SI") == 0)
    return 988;
  else if (strcmp(LaNote, "DOA") == 0)
    return 1046;
  else
    return 0; 
}


//reverse mode function : stores command list in a double dimention grid, upside down, then call Play function.
void reverse (FILE* LeDescripteur, float swiftness)
{
  char LesCommandes[50][50];
  char UneCommande[50];
  char LaNote[6];
  int LaNote2 = 0;
  float LeTemps = 0.0;
  float LeSleep= 0.0;
  int compteur = 0;

  while(fgetc(LeDescripteur) != EOF)
    {
      fscanf(LeDescripteur,"%s %f %f\n",LaNote,&LeTemps,&LeSleep);
      LaNote2 = detectFrequency(LaNote);
      sprintf(UneCommande, "sox -r 8000 -n output.au synth %f sine %d", LeTemps*swiftness, LaNote2);
      strcpy(LesCommandes[compteur],UneCommande);
      compteur++;
    }
  while(compteur != 0)
    {
       play(LesCommandes[compteur]);
       compteur --;
    }
}

// Swiftness function : allows User to define a multiplying/dividing coeficient for the music sample he plays 
float swiftness ()
{
  float OMG_Dat_Choucroute = 1;
  char *OMG_Dat_Ommelette = malloc(sizeof(char)*MAXIMUM_LENGHT);
  

  printf("Voulez vous accelerer(tapez '++')/ralentir(tapez '--') votre morceau ? C pour ne pas modifier \n");

  OMG_Dat_Ommelette = InputHandler(OMG_Dat_Ommelette);
  
  if(strcmp(OMG_Dat_Ommelette, "++") == 0)
    {
      printf("De combien voulez vous accelerer? (en pourcent) \n");
      scanf("%f", &OMG_Dat_Choucroute);
      OMG_Dat_Choucroute = 1-(OMG_Dat_Choucroute/100);
    }
  else if (strcmp(OMG_Dat_Ommelette, "--") == 0) 
    {
      printf("De combien voulez vous ralentir ? (en pourcent) \n");
      scanf("%1f", &OMG_Dat_Choucroute);
      OMG_Dat_Choucroute = 1+(OMG_Dat_Choucroute/100);
    }
  else if (OMG_Dat_Ommelette[0] == 'c' || OMG_Dat_Ommelette[0] == 'C')
    return 1; 

  while (OMG_Dat_Choucroute > 2 || OMG_Dat_Choucroute < 0 )
    {
      printf(" La valeur entrée n'est pas valide ! recommancez \n");
      scanf("%f", &OMG_Dat_Choucroute);
    }
  free(OMG_Dat_Ommelette);
  return OMG_Dat_Choucroute;

}

//safe_check of User input 
char* InputHandler(char * MyString)
{
  int Taille_Courante = MAXIMUM_LENGHT;
  char LeCaractere = NULL;
  int i = 0;

  if(MyString != NULL)
    {
          while( getchar() != '\n')
	{
	  //clear %d characteR
	}   

      while( (LeCaractere=getchar()) != '\n')
	{
	  //LeCaractere = getchar();
	  if( i == Taille_Courante)
	    {
	      Taille_Courante++;
	      MyString = realloc(MyString,Taille_Courante);
	      MyString[i] = LeCaractere;
	    }
	  else
	     MyString[i] = LeCaractere;
	  
	  i++;
	}

    }
  else
    {
      printf("erreur lors de l'allocation memoire");
      return 0;
    }
  return MyString;
}

// User choose the Mode he wants to use
int choixMode()
{
  int LeChoix = NULL;

  printf(" Quel mode voulez vous utiliser ?\n");
  printf("----1) Ramdom Music\n----2)Play from a file\n");
  scanf("%d", &LeChoix);
  while(LeChoix < 1 || LeChoix > 2)
     {
       printf("Ne faites pas l'idiot, choisissez entre 1 et 2\n");
       scanf("%d", &LeChoix);
     }

  return LeChoix;
}


//user chooses mode for the sample he wants to play ( normal or reverse)
int choixModePlay()
{
  int LeModePlay = NULL;
  int i = 1;

  printf("------Plusieurs Options s'offrent à vous--------\n");
  printf("---1)  mode Normal\n");
  printf("---2)  mode Reverse\n");

  do
    {
      scanf("%d", &LeModePlay);
      if(i > 1)
	printf("Ne faites pas l'idiot, choisissez entre 1 et 2\n");

      i++;
    }

  while(LeModePlay < 1 && LeModePlay > 3);
	
  return LeModePlay;
}

// displays a sober command-line interface
void Accueil()
{
  printf("-----------Bienvenu dans le 8-BITIZER-------------\n");
  printf("           ~~~~~~~~~~~~~~~~~~~~~~~~~~             \n\n");
  printf(" Le 8-BITIZER est un programme en ligne de commande qui permet de jouer \n de la musique a partir d'un fichier .txt\n\n");
}

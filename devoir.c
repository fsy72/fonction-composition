#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

extern char *optarg;

int f(int n) {
   int p = 1;
   for(int i=0; i<n; i++)
      p *= 2;
   return p;
}
int g(int n) {  return 2*n; }

void afficher_usage(char *nom_programme) {
   printf("Usage: %s -f n | -g n\n", nom_programme);
   printf("Options:\n");
   printf("  -f n  :  Calcule 2^n\n");
   printf("  -g n  :  Calcule 2*n\n");
   printf("Les options peuvent être combinees pour calculer la composition des fonctions:\n");
   printf("Usage: %s -f n -g\n", nom_programme);
   printf("Oubien: %s -g n -f\n", nom_programme);
}

int main(int argc, char *argv[]) {
   int opt;
   int f_present = 0, g_present = 0;
   int n_value = 0;
   // int n_value = 0;

   if (argc<3) {
      printf("Nombre d'argument insuffisant\n");
      afficher_usage(argv[0]);
      exit(1);
   }
   
   while ((opt = getopt(argc, argv, ":f:g:")) != -1) {
      switch (opt) {
         case 'f':
            f_present = 1;
            if(!g_present)
               n_value = atoi(optarg);
            break;
         case 'g':
            g_present = 1;
            if(!f_present)
               n_value = atoi(optarg);
            break;
         case ':':
            if (f_present) 
               if(!strcmp(argv[3],"-g")){
                  printf("fog(%d) = f(g(%d)) = 2^(2*%d) = %d\n", n_value, n_value, n_value, f(g(n_value)));
               } else
                  afficher_usage(argv[0]);
            else 
               if (g_present) 
                  if(!strcmp(argv[3],"-f")){
                     printf("gof(%d) = g(f(%d)) = 2*(2^%d) = %d\n", n_value, n_value, n_value, g(f(n_value)));
                  } else
                     afficher_usage(argv[0]);
            return 0;
         case '?':
            fprintf(stderr, "Option inconnue ou argument manquant\n");
            afficher_usage(argv[0]);
            return 1;
      }
   }
   
   if (!f_present && !g_present) {
      fprintf(stderr, "Au moins une option -f ou -g est requise\n");
      afficher_usage(argv[0]);
      exit(1);
   }
   
   if (f_present && !g_present) {
      // Cas f(n)
      if(n_value < 0)
         printf("f(%d) = 2^%d = %.3f\n", n_value, n_value, (1.0/f(-n_value)));
      else
         printf("f(%d) = 2^%d = %d\n", n_value, n_value, f(n_value));
   }
   else {
      if (g_present && !f_present) {
         // Cas g(n)
         printf("g(%d) = 2*%d = %d\n", n_value, n_value, g(n_value));
      } else
         afficher_usage(argv[0]);
   }

   return 0;
}

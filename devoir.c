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
int fog(int n) {    return f(g(n)); }
int gof(int n) {    return g(f(n)); }

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
   int n_value_f = 0;
   int n_value_g = 0;
   char ordre[2];
   int ordre_idx = 0;
   int resultat;
   
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
               n_value_f = atoi(optarg);
            ordre[ordre_idx++] = 'f';
            break;
         case 'g':
            g_present = 1;
            if(!f_present)
               n_value_g = atoi(optarg);
            ordre[ordre_idx++] = 'g';
            break;
         case ':':
            if (f_present) {
               // fog(n)
               resultat = fog(n_value_f);
               printf("fog(%d) = f(g(%d)) = 2^(2*%d) = %d\n", 
               n_value_f, n_value_f, n_value_f, resultat);
            }
            else if (g_present) {
               // gof(n)
               resultat = gof(n_value_g);
               printf("gof(%d) = g(f(%d)) = 2*(2^%d) = %d\n", 
               n_value_g, n_value_g, n_value_g, resultat);
            }
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
      resultat = f(n_value_f);
      printf("f(%d) = 2^%d = %d\n", n_value_f, n_value_f, resultat);
   }
   else {
      if (g_present && !f_present) {
         // Cas g(n)
         resultat = g(n_value_g);
         printf("g(%d) = 2*%d = %d\n", n_value_g, n_value_g, resultat);
      }
   }

   return 0;
}

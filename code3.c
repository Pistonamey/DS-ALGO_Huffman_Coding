/* Name - Amey Shinde
   Student ID - 1001844387
   Command for Compilation - "gcc code3.c"
   Command for output using the file given by Proffessor - "a.out lab3fall21.a.dat"
*/
#include <stdio.h>
#include <string.h>

double p[20];
int n;
double c[20][20];
int trace[20][20];

void tree(int left, int right, int indent)
{
  int i;

  if (left == right) // At a leaf in the optimal tree
  {
    for (i = 0; i < indent; i++)
    {
      printf("   ");
    }
    printf("%d\n", left);

    return;
  }

  tree(trace[left][right] + 1, right, indent + 1); // Print the right subtree for c(left,right)

  for (i = 0; i < indent; i++)
  {
    printf("   ");
  }
  printf("%d %d   cost : %lf\n", left, right, c[left][right]); // Print the root
  tree(left, trace[left][right], indent + 1);                  // Print the left subtree for c(left,right)
}

int main(int argc, char *argv[])
{

  FILE *fp;
  fp = fopen(argv[1], "r");
  int i, j, k;
  double work;
  double sum = 0.00;
  double work2;
  int l;

  fscanf(fp, "%d", &n); // Get the number of matrices

  for (i = 0; i <= n; i++)
    fscanf(fp, "%lf", &p[i]); // Get the dimensions

  //printf("%0.8f\n", p[4]);
  for (i = 0; i < n; i++)
    c[i][i] = trace[i][i] = 0; // Process base case

  for (i = 1; i < n; i++)
  {
    // The difference between leftmost and rightmost matrix indices
    for (j = 0; j <= n - i; j++) // Leftmost index
    {
      sum = 0.00;

      work2 = 999999.00; // Initialize as infinity, then improve

      for (l = j; l <= j + i; l++)
      {
        sum = sum + p[l];
      }
      // k is the last matrix index for the left subtree, k+1 is the first matrix index for the right subtree
      for (k = j; k < j + i; k++)
      {
        work = c[j][k] + c[k + 1][j + i];

        if (work2 > work) // Is work an improvement?
        {
          work2 = work;
          c[j][j + i] = (work2 + sum);

          trace[j][j + i] = k;
        }
      }
    }
  }

  printf("   ");
  for (i = 0; i < n; i++)
    printf("   %9d   ", i);
  printf("\n");
  for (i = 0; i < n; i++)
  {
    printf("%2d ", i);
    for (j = 0; j < n; j++)
      if (i > j)
        printf(" ------------- "); // c(i,j) is not a thing
      else
        printf(" %3f %4d ", c[i][j], trace[i][j]);
    printf("\n");

    printf("\n");
  }

  tree(0, n - 1, 0); // Print the tree for the optimal strategy
}

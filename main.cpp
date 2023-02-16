/* --------------------------------------------------------------------------- *
 *  _   _______ _____ _____                                                    *
 * | | | |  ___/  __ \  __ \                                                   *
 * | | | | |_  | /  \/ |  \/                                                   *
 * | | | |  _| | |   | | __                                                    *
 * | |_| | |   | \__/\ |_\ \                                                   *
 *  \___/\_|    \____/\____/                                                   *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 * UFCG - Universidade Federal de Campina Grande                               *
 * LARCA - Laboratório de Referência em Controle e Automação                   *
 * --------------------------------------------------------------------------- *
 * P&D CHESF TC/IEC61850                                                       *
 * Sistema digital para correção de distorções de corrente no secundário de TC *
 *                                                                             *
 * Descrição: O projeto tem como objetivos: Aperfeiçoar um modelo de transfor- *
 * mador de corrente (TC) já desenvolvido, no qual são representados os  efei- *
 * tos de saturação, histerese, perdas parasíticas clássicas e perdas  dinâmi- *
 * cas. Elaborar rotinas em linguagem C++, com objetivo de descrever o compor- *
 * tamento do modelo considerado de TC nos regimes permanente e transitório,   *
 * incluindo aplicações em tempo real.                                         *
 * --------------------------------------------------------------------------- *
 * Arquivo: dsp_tc.cpp                                                         *
 * Autor..: Ericson Norberto                                                   *
 *                                                                             *
 * Created on 16 de August de 2014, 19:55                                      *
 * Ultima modificacao: 26/10/2014                                              *
 * --------------------------------------------------------------------------- */
#include "dsp_blas.hpp"

/* Função principal */
int main(int argc, char** argv)
{
    /* Declaracoes iniciais */
    size_t t_lin_a = 4;
    size_t t_col_a = 4;

    size_t t_lin_b = 4;
    size_t t_col_b = 4;

    size_t t_size_i = 4;

    /* Instancia um objeto blas */
    dsp_blas t_blas;

    /* Declara uma variável do tipo matriz */
    blas_matrix* t_matriz_a;
    blas_matrix* t_matriz_b;
    blas_matrix* t_matriz_p;
    blas_matrix* t_matriz_i;

    /* Valores máximos */
    double t_max_a, t_max_b, t_max_p;

    /* Valores mínimos */
    double t_min_a, t_min_b, t_min_p;

    /* Constante */
    double t_k = 1.823457828327293;

    /* Inicializa a matriz */
    t_matriz_a = t_blas.blas_matrix_init(t_lin_a, t_col_a);
    t_matriz_b = t_blas.blas_matrix_init(t_lin_b, t_col_b);

    /* Atribui um valor aos elementos da matriz - MATRIZ ALEATORIA (MATLAB) */
    t_blas.blas_matrix_set(t_matriz_a, 0, 0, 0.8147);
    t_blas.blas_matrix_set(t_matriz_a, 0, 1, 0.6324);
    t_blas.blas_matrix_set(t_matriz_a, 0, 2, 0.9575);
    t_blas.blas_matrix_set(t_matriz_a, 0, 3, 0.9572);

    t_blas.blas_matrix_set(t_matriz_a, 1, 0, 0.9058);
    t_blas.blas_matrix_set(t_matriz_a, 1, 1, 0.0975);
    t_blas.blas_matrix_set(t_matriz_a, 1, 2, 0.9649);
    t_blas.blas_matrix_set(t_matriz_a, 1, 3, 0.4854);

    t_blas.blas_matrix_set(t_matriz_a, 2, 0, 0.1270);
    t_blas.blas_matrix_set(t_matriz_a, 2, 1, 0.2785);
    t_blas.blas_matrix_set(t_matriz_a, 2, 2, 0.1576);
    t_blas.blas_matrix_set(t_matriz_a, 2, 3, 0.8003);

    t_blas.blas_matrix_set(t_matriz_a, 3, 0, 0.9134);
    t_blas.blas_matrix_set(t_matriz_a, 3, 1, 0.5469);
    t_blas.blas_matrix_set(t_matriz_a, 3, 2, 0.9706);
    t_blas.blas_matrix_set(t_matriz_a, 3, 3, 0.1419);

//    for (size_t i=0; i<t_lin_a; i++)
//    {
//        for (size_t j=0; j<t_col_a; j++)
//        {
//            t_blas.blas_matrix_set(t_matriz_a, i, j, (i*j)+0.5);
//        }
//    }

    /* Imprime a matriz incializada em tela */
    printf("INCICIALIZACAO MATRIZ %dX%d - t_matriz_a - ************************\n", t_lin_a, t_col_a);
    for (size_t i=0; i<t_lin_a; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_a, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Inicializa matriz identidade */
    t_matriz_i = t_blas.blas_matrix_init_identity(t_size_i);
    printf("INCICIALIZACAO MATRIZ IDENTIDADE %dX%d - t_matriz_i - *************\n", t_size_i, t_size_i);
    for (size_t i=0; i<t_size_i; i++)
    {
        for (size_t j=0; j<t_size_i; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_i, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Atribui um valor aos elementos da matriz - MATRIZ ALEATORIA (MATLAB) */
    t_blas.blas_matrix_set(t_matriz_b, 0, 0, 0.4218);
    t_blas.blas_matrix_set(t_matriz_b, 0, 1, 0.6557);
    t_blas.blas_matrix_set(t_matriz_b, 0, 2, 0.6787);
    t_blas.blas_matrix_set(t_matriz_b, 0, 3, 0.6555);

    t_blas.blas_matrix_set(t_matriz_b, 1, 0, 0.9157);
    t_blas.blas_matrix_set(t_matriz_b, 1, 1, 0.0357);
    t_blas.blas_matrix_set(t_matriz_b, 1, 2, 0.7577);
    t_blas.blas_matrix_set(t_matriz_b, 1, 3, 0.1712);

    t_blas.blas_matrix_set(t_matriz_b, 2, 0, 0.7922);
    t_blas.blas_matrix_set(t_matriz_b, 2, 1, 0.8491);
    t_blas.blas_matrix_set(t_matriz_b, 2, 2, 0.7431);
    t_blas.blas_matrix_set(t_matriz_b, 2, 3, 0.7060);

    t_blas.blas_matrix_set(t_matriz_b, 3, 0, 0.9595);
    t_blas.blas_matrix_set(t_matriz_b, 3, 1, 0.9340);
    t_blas.blas_matrix_set(t_matriz_b, 3, 2, 0.3922);
    t_blas.blas_matrix_set(t_matriz_b, 3, 3, 0.0318);

    /* Imprime uma segunda matriz incializada em tela */
    printf("INCICIALIZACAO MATRIZ %dX%d - t_matriz_b - ************************\n", t_lin_b, t_col_b);
    for (size_t i=0; i<t_lin_b; i++)
    {
        for (size_t j=0; j<t_col_b; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_b, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Multiplica a matriz t_matriz_b por um escalar */
    t_blas.blas_matrix_scale(t_matriz_b, t_k);
    printf("MULTIPLICA A MATRIZ t_matriz_b (%dX%d) POR ESCALAR %f *******\n", t_lin_b, t_col_b, t_k);
    for (size_t i=0; i<t_lin_b; i++)
    {
        for (size_t j=0; j<t_col_b; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_b, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Multiplica a matriz t_matriz_b por por t_matriz_a */
    t_matriz_p = t_blas.blas_matrix_mul_elements(t_matriz_b, t_matriz_a);
    printf("MULTIPLICA t_matriz_b(%dX%d) POR t_matriz_a(%dX%d) - t_matriz_p(%dX%d) *******\n", t_lin_b, t_col_b, t_lin_a, t_col_a, t_lin_b, t_col_a);
    for (size_t i=0; i<t_lin_b; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_p, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Efetua a soma de duas matrizes (t_matriz_a com t_matriz_b) */
    t_blas.blas_matrix_add(t_matriz_a, t_matriz_b);
    printf("EFETUA A SOMA DE 2 MATRIZES t_matriz_a (%dX%d) + t_matriz_b (%dX%d)*******\n", t_lin_a, t_col_a, t_lin_b, t_col_b);
    for (size_t i=0; i<t_lin_a; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_a, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Soma uma constante à matriz t_matriz_a */
    t_blas.blas_matrix_add_constant(t_matriz_a, t_k);
    printf("SOMA UMA CONSTANTE A MATRIZ t_matriz_a (%dX%d) ***********\n", t_lin_a, t_col_a);
    for (size_t i=0; i<t_lin_a; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_a, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Efetua a subtracao de duas matrizes (t_matriz_a com t_matriz_b) */
    t_blas.blas_matrix_sub(t_matriz_a, t_matriz_b);
    printf("EFETUA A SUBTRACAO DE 2 MATRIZES t_matriz_a (%dX%d) - t_matriz_b (%dX%d)*******\n", t_lin_a, t_col_a, t_lin_b, t_col_b);
    for (size_t i=0; i<t_lin_a; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_matriz_a, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Obtem o valor máximo das matrizes t_matriz_a, t_matriz_b e t_matriz_p */
    t_max_a = t_blas.blas_matrix_max(t_matriz_a);
    t_max_b = t_blas.blas_matrix_max(t_matriz_b);
    t_max_p = t_blas.blas_matrix_max(t_matriz_p);
    printf("VALORES MAXIMOS *************************************************\n");
    printf("MAX(t_matriz_a)=%f\nMAX(t_matriz_b)=%f\nMAX(t_matriz_p)=%f\n", t_max_a, t_max_b, t_max_p);
    printf("*****************************************************************\n");

    /* Obtem o valor mínimo das matrizes t_matriz_a, t_matriz_b e t_matriz_p */
    t_min_a = t_blas.blas_matrix_min(t_matriz_a);
    t_min_b = t_blas.blas_matrix_min(t_matriz_b);
    t_min_p = t_blas.blas_matrix_min(t_matriz_p);
    printf("VALORES MINIMOS *************************************************\n");
    printf("MIN(t_matriz_a)=%f\nMIN(t_matriz_b)=%f\nMIN(t_matriz_p)=%f\n", t_min_a, t_min_b, t_min_p);
    printf("*****************************************************************\n");

    /* Obtem as normas das matrizes t_matriz_a, t_matriz_b e t_matriz_p */
    printf("NORMAS DAS MATRIZES *********************************************\n");
    printf("NORMA(t_matriz_a,inf)=%f\nNORMA(t_matriz_b,inf)=%f\nNORMA(t_matriz_p,inf)=%f\n",
            t_blas.blas_matrix_norm(t_matriz_a, false), t_blas.blas_matrix_norm(t_matriz_b, false),
            t_blas.blas_matrix_norm(t_matriz_p, false));
    printf("*****************************************************************\n");

    /* Declaração de matrizes */
    blas_matrix* t_invA;
    blas_matrix* t_invB;
    blas_matrix* t_invP;

    /* Inicializando a matriz t_A */
    t_invA = t_blas.blas_matrix_init(t_lin_a, t_col_a);
    t_invB = t_blas.blas_matrix_init(t_lin_b, t_col_b);
    t_invP = t_blas.blas_matrix_init(t_lin_b, t_col_a);

    /* Obtem a inversa das matrizes A, B e P */
    t_invA = t_blas.blas_matrix_LU_Ivert(t_matriz_a);
    t_invB = t_blas.blas_matrix_LU_Ivert(t_matriz_b);
    t_invP = t_blas.blas_matrix_LU_Ivert(t_matriz_p);

    /* Imprime a matriz t_matriz_a */
    printf("IMPRIME A MATRIZ INVERSA - inv(t_matriz_a) (%dX%d) *******\n", t_lin_a, t_col_a);
    for (size_t i=0; i<t_lin_a; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_invA, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Imprime a matriz t_matriz_b */
    printf("IMPRIME A MATRIZ INVERSA - inv(t_matriz_b) (%dX%d) *******\n", t_lin_b, t_col_b);
    for (size_t i=0; i<t_lin_a; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_invB, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Imprime a matriz t_matriz_p */
    printf("IMPRIME A MATRIZ INVERSA - inv(t_matriz_p) (%dX%d) *******\n", t_lin_b, t_col_a);
    for (size_t i=0; i<t_lin_b; i++)
    {
        for (size_t j=0; j<t_col_a; j++)
        {
            printf("(%d,%d)=%f   ", i, j, t_blas.blas_matrix_get(t_invP, i, j));
        }
        printf("\n");
    }
    printf("*****************************************************************\n");

    /* Libera memória alocada */
    t_blas.blas_matrix_free(t_matriz_a);
    t_blas.blas_matrix_free(t_matriz_b);
    t_blas.blas_matrix_free(t_matriz_p);
    t_blas.blas_matrix_free(t_matriz_i);

    /* Libera memória alocada */
    t_blas.blas_matrix_free(t_invA);
    t_blas.blas_matrix_free(t_invB);
    t_blas.blas_matrix_free(t_invP);

    return EXIT_SUCCESS;
}

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
 * Arquivo: dsp_blas.hpp                                                       *
 * Autor..: Ericson Norberto                                                   *
 *                                                                             *
 * Created on 16 de August de 2014, 19:55                                      *
 * Ultima modificacao: 26/10/2014                                              *
 * --------------------------------------------------------------------------- */
#include "dsp_blas.hpp"

dsp_blas::dsp_blas()
{
    cout << "dsp_blas: constructor called" << endl;
}

dsp_blas::~dsp_blas()
{
    cout << "dsp_blas: destructor called" << endl;
}

///
///
///
blas_matrix* dsp_blas::blas_matrix_init(const size_t p_lin, const size_t p_col)
{
    /* Declaração de variáveis e alocação de memória */
    blas_matrix *t_return = new blas_matrix;
    
    /* Aloca memória para os elementos do tipo double */
    t_return->t_value = new double[p_lin*p_col];
    
    /* Armazena o total de linhas e colunas da matrix */
    t_return->t_lin = p_lin;
    t_return->t_col = p_col;
    
    /* Inicialização de elementos da matriz */
    for (size_t i=0; i<(p_lin*p_col); i++)
    {
        t_return->t_value[i] = 0;
    }
    
    return t_return;
}

///
///
///
blas_matrix* dsp_blas::blas_matrix_init_identity(const size_t p_size)
{
    /* Declaração de variáveis e alocação de memória */
    blas_matrix *t_return = new blas_matrix;
 
    /* Aloca memória para os elementos do tipo double */
    t_return->t_value = new double[p_size*p_size];
    
    /* Armazena o total de linhas e colunas da matrix */
    t_return->t_lin = p_size;
    t_return->t_col = p_size;
    
    /* Inicialização de elementos da matriz */
    for (size_t i=0; i<p_size; i++)
    {
        for (size_t j=0; j<p_size; j++)
        {
            if (i == j)
            {
                t_return->t_value[i*p_size+j] = 1;
            }
            else
            {
                t_return->t_value[i*p_size+j] = 0;
            }
        }
    }
    
    return t_return;
}

///
///
///
void dsp_blas::blas_matrix_set_identity(blas_matrix* p_m)
{
    /* Declaracao de variáveis */
    size_t t_lin, t_col;
    
    /* Armazena o total de linhas e colunas da matrix */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Inicialização de elementos da matriz */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            if (i == j)
            {
                p_m->t_value[i*t_col+j] = 1;   
            }
            else
            {
                p_m->t_value[i*t_col+j] = 0;
            }
        }
    }
}

///
///
///
void dsp_blas::blas_matrix_set(blas_matrix* p_m, const size_t p_lin, const size_t p_col, double p_value)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Atribui valor ao elemento da matriz */
    p_m->t_value[p_lin*t_col+p_col] = p_value;
}

///
///
///
void dsp_blas::blas_matrix_set_zero(blas_matrix* p_m)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Atribui valor ao elemento da matriz */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            p_m->t_value[i*t_col+j] = 0;
        }
    }
    
}

///
///
///
double dsp_blas::blas_matrix_get(const blas_matrix* p_m, const size_t p_lin, const size_t p_col)
{
    /* Declaração de variáveis */
    double t_return = 0;
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Atribui valor ao elemento da matriz */
    t_return = p_m->t_value[p_lin*t_col+p_col];
    
    return t_return;
}

///
///
///
void dsp_blas::blas_matrix_scale(blas_matrix* p_m, double p_value)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Efetua o produto de todos os elementos da matriz por um escalar t_k */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            p_m->t_value[i*t_col+j] = p_value*p_m->t_value[i*t_col+j];
        }
    }
}

///
///
///
blas_matrix* dsp_blas::blas_matrix_mul_elements(const blas_matrix* p_m, const blas_matrix* p_n)
{
    /* Declaração de variáveis */
    size_t t_lin1, t_col1, t_lin2, t_col2;
    double t_val = 0;
    
    /* Obtem as dimensões das matrizes */
    t_lin1 = p_m->t_lin;
    t_col1 = p_m->t_col;
    t_lin2 = p_n->t_lin;
    t_col2 = p_n->t_col;
    
    /* Dimensao da matriz gerada */
    blas_matrix* t_return = blas_matrix_init(t_lin1, t_col2);
    
    /* Efetua o produto de duas matrizes */
    for (size_t i=0; i<t_col2; i++)
    {
        for (size_t j=0; j<t_lin1; j++)
        {
            for (size_t k=0; k<t_col1; k++)
            {
                t_val = t_val+(p_m->t_value[j*t_col1+k]*p_n->t_value[k*t_lin2+i]);
            }
            blas_matrix_set(t_return, j, i, t_val);
            t_val = 0;
        }
    }
    
    return t_return;
}

///
///
///
void dsp_blas::blas_matrix_add(blas_matrix* p_m, const blas_matrix* p_n)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Efetua o produto de duas matrizes */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            p_m->t_value[i*t_col+j]=p_m->t_value[i*t_col+j]+p_n->t_value[i*t_col+j];
        }
    }
}

///
///
///
void dsp_blas::blas_matrix_add_constant(blas_matrix* p_m, double p_k)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Efetua o produto de todos os elementos da matriz por um escalar t_k */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            p_m->t_value[i*t_col+j] = p_k+p_m->t_value[i*t_col+j];
        }
    }
}

///
///
///
void dsp_blas::blas_matrix_sub(blas_matrix* p_m, const blas_matrix* p_n)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Efetua o produto de duas matrizes */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            p_m->t_value[i*t_col+j]=p_m->t_value[i*t_col+j]-p_n->t_value[i*t_col+j];
        }
    }
}

///
///
///
double dsp_blas::blas_matrix_max(const blas_matrix* p_m)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Registrador de máximo */
    double t_return;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Verifica qual o maior dos elementos da matriz */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            if ((i*t_col+j) == 0)
            {
                /* Armazena um valor da matriz */
                t_return = p_m->t_value[i*t_col+j];
            }
            else
            {
                if (t_return < p_m->t_value[i*t_col+j])
                {
                    t_return = p_m->t_value[i*t_col+j];
                }
            }
        }
    }
    
    return t_return;
}

///
///
///
double dsp_blas::blas_matrix_min(const blas_matrix* p_m)
{
    /* Declaração de variáveis */
    size_t t_lin, t_col;
    
    /* Registrador de máximo */
    double t_return;
    
    /* Obtem o total de linhas da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Verifica qual o menor dos elementos da matriz */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            if ((i*t_col+j) == 0)
            {
                /* Armazena um valor da matriz */
                t_return = p_m->t_value[i*t_col+j];
            }
            else
            {
                if (t_return > p_m->t_value[i*t_col+j])
                {
                    t_return = p_m->t_value[i*t_col+j];
                }
            }
        }
    }
    
    return t_return;
}

///
///
///
void dsp_blas::blas_matrix_LU(const blas_matrix* p_A, blas_matrix* p_L, blas_matrix* p_U)
{
    /* Declaração de variáveis */
    double t_val_L = 0;
    double t_val_U = 0;
    double t_val_b = 0;
    //double t_val_x = 0;
    
    /* Dimensoes das matrizes */
    size_t t_lin = 0;
    size_t t_col = 0;
    
    /* Obtem as dimensoes das matrizes */
    t_lin = p_A->t_lin;
    t_col = p_A->t_col;
    
    /* Copia o conteudo da matriz A para a matriz U */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            blas_matrix_set(p_U, i, j, blas_matrix_get(p_A, i, j));
        }
    }
    
    /* Verifica se a matriz é singular */
    if (blas_matrix_get(p_U, 0, 0) == 0)
    {
        cout << "dsp_blas::blas_matrix_LU(): singular.. LU impossivel.." << endl;
        return;
    }
    
    /* Pivoteamento */
    for (size_t j=0; j<(t_col-1); j++)
    {
        for (size_t i=1; i<t_lin; i++)
        {
            if (i > j)
            {
                t_val_L = blas_matrix_get(p_U, i, j)/blas_matrix_get(p_U, j, j);
                for (size_t k=j; k<t_col; k++)
                {
                    t_val_U = blas_matrix_get(p_U, i, k)-(t_val_L*blas_matrix_get(p_U, j, k));
                    blas_matrix_set(p_U, i, k, t_val_U);
                    t_val_U = 0;
                }
                blas_matrix_set(p_L, i, j, t_val_L);
            }
        }
    }
    
    /* Substituicao reversa para matriz L */
    for (size_t i=0; i<t_lin; i++)
    {
        for (size_t j=0; j<t_col; j++)
        {
            t_val_b = blas_matrix_get(p_L, i, j);
        }
    }
    
}

///
///
///
blas_matrix* dsp_blas::blas_matrix_LU_Ivert(const blas_matrix* p_m)
{
    /* Definição de variáveis */
    double t_val_a = 0;
    double t_val_b = 0;
    double t_val_u = 0;
    double t_val_i = 0;
    double t_val_x = 0;

    /* Declaracao de variaveis */
    size_t t_lin;
    size_t t_col;
    
    /* Atualiza as linhas e colunas */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Checa se a matriz é quadrada */
    if (t_lin != t_col)
    {
        cout << "dsp_blas::blas_matrix_LU_Ivert(): matriz nao e quadradada, inversao impossivel ..." << endl;
        return NULL;
    }
    
    /* Declaração de matrizes */
    blas_matrix* t_L = blas_matrix_init_identity(t_lin);
    blas_matrix* t_U = blas_matrix_init_identity(t_lin);
    blas_matrix* t_I = blas_matrix_init_identity(t_lin);
    blas_matrix* t_B = blas_matrix_init(t_lin, t_col);
    
    /* Matriz com a inversa de retorno */
    blas_matrix* t_Ai = blas_matrix_init(t_lin, t_col);
    
    /* Obtem as matrizes LU */
    blas_matrix_LU(p_m, t_L, t_U);

    /* Cálculo da matriz inversa intermediaria B */
    for (size_t k=0; k<t_col; k++)
    {
        for (size_t i=0; i<t_lin; i++)
        {
            t_val_i = blas_matrix_get(t_I, i, k);
            for (size_t j=0; j<t_col; j++)
            {
                if (i != j)
                {
                    t_val_a = blas_matrix_get(t_L, i, j);
                    t_val_b = blas_matrix_get(t_B, j, k);
                    t_val_x = t_val_x-(t_val_a*t_val_b);
                }
            }
            blas_matrix_set(t_B, i, k, (t_val_i+t_val_x));
            t_val_x = 0;
        }
    }
    
    /* Reseta variáveis */
    t_val_a = 0;
    t_val_b = 0;
    t_val_u = 0;
    t_val_x = 0;
    
    /* Cálculo da matriz inversa */
    for (size_t k=0; k<t_col; k++)
    {
        for (int i=(t_lin-1); i>-1; i--)
        {
            t_val_b = blas_matrix_get(t_B, i, k);
            for (size_t j=0; j<t_col; j++)
            {
                if (i != j)
                {
                    t_val_u = blas_matrix_get(t_U, i, j);
                    t_val_x = blas_matrix_get(t_Ai, j, k);
                    t_val_a = t_val_a-(t_val_u*t_val_x);
                }
            }
            blas_matrix_set(t_Ai, i, k, (t_val_b+t_val_a)/(blas_matrix_get(t_U, i, i)));
            t_val_a = 0;
        }
    }
    
    /* Retorna a matriz invertida */
    return t_Ai;
}

///
///
///
double dsp_blas::blas_matrix_norm(const blas_matrix* p_m, bool p_euclidian)
{
    /* Inicializacao das variáveis */
    size_t t_lin = 0;
    size_t t_col = 0;
    
    /* Obtem a dimensão da matriz */
    t_lin = p_m->t_lin;
    t_col = p_m->t_col;
    
    /* Inicializacao de variável */
    double t_return = 0;
    double t_sum = 0;
    
    /* Verifica o tipo de norma. true->euclidiana, false-> norma do máximo */
    if (p_euclidian == false)
    {
        for (size_t i=0; i<t_lin; i++)
        {
            for (size_t j=0; j<t_col; j++)
            {
                t_sum = t_sum+abs(blas_matrix_get(p_m, i, j));
            }
            if (t_return < t_sum)
            {
                t_return = t_sum;
            }
            t_sum = 0;
        }
    }
    else
    {
    }
    
    return t_return;
}

///
///
///
void dsp_blas::blas_matrix_free(blas_matrix* p_matrix)
{
    /* Deleta os elementos da maitriz de dados */
    delete[] p_matrix->t_value;
    
    /* Delete a matriz */
    delete p_matrix;
    
    cout << "dsp_blas::blas_matrix_free(): deallocated memory" << endl;
}
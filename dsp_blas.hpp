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
#ifndef DSP_BLAS_HPP
    #define DSP_BLAS_HPP

#include "dsp_defines.hpp"

using namespace std;

class dsp_blas
{
    public:
        /* Construtor default */
        dsp_blas();
        /* Destrutor default */
        virtual ~dsp_blas();
        /* Aloca memória para uma variável do tipo t_matrix */
        blas_matrix* blas_matrix_init(const size_t p_lin, const size_t p_col);
        /* Aloca memoria para uma variável do tipo t_matrix */
        blas_matrix* blas_matrix_init_identity(const size_t p_size);
        /* Define uma matriz incializada como matriz identidade */
        void blas_matrix_set_identity(blas_matrix* p_m);
        /* Atribui um valor à uma posicao (i,j) de uma matriz */
        void blas_matrix_set(blas_matrix* p_m, const size_t p_lin, const size_t p_col, double p_value);
        /* Atribui o valor zero à todos os elementos da matriz p_m */
        void blas_matrix_set_zero(blas_matrix* p_m);
        /* Obtem o valor de uma posicao (i,j) de uma matriz */
        double blas_matrix_get(const blas_matrix* p_m, const size_t p_lin, const size_t p_col);
        /* Multiplica uma matriz por um escalar */
        void blas_matrix_scale(blas_matrix* p_m, double p_value);
        /* Multiplica duas matrizes e armazena */
        blas_matrix* blas_matrix_mul_elements(const blas_matrix* p_m, const blas_matrix* p_n);
        /* Soma duas matrizes e armazena o resultado na matriz p_m */
        void blas_matrix_add(blas_matrix* p_m, const blas_matrix* p_n);
        /* Soma um valor à uma matriz e armazena o resultado em p_m */
        void blas_matrix_add_constant(blas_matrix* p_m, double p_value);
        /* Subtrai duas matrizes e armazena o resultado em p_m */
        void blas_matrix_sub(blas_matrix* p_m, const blas_matrix* p_n);
        /* Retorna o elemento de máximo valor da matriz p_m */
        double blas_matrix_max(const blas_matrix* p_m);
        /* Retorna o elemento de valor mínimo da matriz p_m */
        double blas_matrix_min(const blas_matrix* p_m);
        /* Obtem por decomposicao as matrizes LU */
        void blas_matrix_LU(const blas_matrix* p_A, blas_matrix* p_L, blas_matrix* p_U);
        /* Obtem a matriz inversa de p_m */
        blas_matrix* blas_matrix_LU_Ivert(const blas_matrix* p_m);
        /* Retorna a norma maxima (infinito) da matriz p_m */
        double blas_matrix_norm(const blas_matrix* p_m, bool p_euclidian);
        /* Desaloca memória alocada */
        void blas_matrix_free(blas_matrix* p_matrix);
        
    private:

};
#endif	/* DSP_BLAS_HPP */
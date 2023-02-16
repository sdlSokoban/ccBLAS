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
#ifndef DSP_DEFINES_HPP
    #define DSP_DEFINES_HPP

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <stdio.h>
#include <fstream>
#include <sys/stat.h>

using namespace std;

struct t_vec
{
    size_t  t_lin;
    size_t  t_col;
    double* t_value;
};
typedef t_vec blas_matrix;

typedef unsigned int u_int;

#define t_pi 3.141592653589793

#endif	/* DSP_DEFINES_HPP */

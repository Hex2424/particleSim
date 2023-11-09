/**
 * @file vector.h
 *
 * MORE INFO ABOUT THE FILE'S CONTENTS
 *
 * @copyright This file is a part of the project particleSim and is distributed under MIT license which
 * should have been included with the project. If not see: https://choosealicense.com/licenses/mit/
 *
 * @author Markas Vielavičius (markas.vielavicius@bytewall.com)
 *
 * @date 2023-11-09
 */


#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdint.h>

typedef struct
{
    float x;
    float y;
}Vector_t;

typedef Vector_t* VectorHandle_t;


void Vector_calcResultant(const VectorHandle_t const vectorA, const VectorHandle_t const vectorB, VectorHandle_t const result)


#endif // VECTOR_H_
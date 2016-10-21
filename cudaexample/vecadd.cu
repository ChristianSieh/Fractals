/*
        ***** vecadd.cu *****

CUDA program to add two vectors.

Compile:    nvcc -o vecadd vecadd.cu
Usage:      vecadd [N], where N is vector length

Author: John M. Weiss, Ph.D.
CSC433/533 Computer Graphics - Fall 2016.

Modifications:
*/

#include <chrono>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;


// sequential vector addition (on the host)
void add_seq( int *a, int *b, int *c, int n )
{
    for ( int i = 0; i < n; i++ )
        c[i] = a[i] + b[i];
}

// CUDA kernel: add two ints in parallel
__global__ void add_par( int *a, int *b, int *c, int n )
{
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if ( i < n ) c[i] = a[i] + b[i];
}

// generate array of random ints with values between 0 and n-1
void random_ints( int array[], int n )
{
    for ( int i = 0; i < n; i++ )
        array[i] = rand() % n;
}

int main( int argc, char** argv )
{
    int n = 1024;
    if ( argc > 1 ) n = atoi( argv[1] );

    // alloc host memory for vectors a, b, c
    int size = n * sizeof( int );
    int *a = ( int * )malloc( size );
    int *b = ( int * )malloc( size );
    int *c_seq = ( int * )malloc( size );
    int *c_par = ( int * )malloc( size );

    // fill arrays a and b with random ints
    srand( time( NULL ) );
    random_ints( a, n );
    random_ints( b, n );

    // add vectors sequentially
    auto c = chrono::system_clock::now();
    add_seq( a, b, c_seq, n );
    chrono::duration<double> d_cpu = chrono::system_clock::now() - c;

    // alloc device  memory for vectors a, b, c
    int *d_a, *d_b, *d_c;
    cudaMalloc( ( void ** )&d_a, size );
    cudaMalloc( ( void ** )&d_b, size );
    cudaMalloc( ( void ** )&d_c, size );

    // copy vectors a and b to device
    cudaMemcpy( d_a, a, size, cudaMemcpyHostToDevice );
    cudaMemcpy( d_b, b, size, cudaMemcpyHostToDevice );

    // launch add() kernel on GPU with M threads per block, (N+M-1)/M blocks
    int nThreads = 64;                              // should be multiple of 32 (up to 1024)
    int nBlocks = ( n + nThreads - 1 ) / nThreads;
    c = chrono::system_clock::now();
    add_par<<< nBlocks, nThreads >>>(d_a, d_b, d_c, n);
    chrono::duration<double> d_gpu = chrono::system_clock::now() - c;

    // copy vector sum back to host
    cudaMemcpy( c_par, d_c, size, cudaMemcpyDeviceToHost );

    #if 0
    cout << "\na:    ";
    for ( int i = 0; i < n; i++ ) cout << " " << a[i];
    cout << "\nb:    ";
    for ( int i = 0; i < n; i++ ) cout << " " << b[i];
    cout << "\nc_seq:";
    for ( int i = 0; i < n; i++ ) cout << " " << c_seq[i];
    cout << "\nc_par:";
    for ( int i = 0; i < n; i++ ) cout << " " << c_par[i];
    #endif

    cout << "\n\nBenchmarks: CPU " << d_cpu.count() << " sec, GPU " << d_gpu.count() << " sec\n\n";

    // cleanup
    free( a ); free( b ); free( c_seq ); free( c_par );
    cudaFree( d_a ); cudaFree( d_b ); cudaFree( d_c );
    return 0;
}

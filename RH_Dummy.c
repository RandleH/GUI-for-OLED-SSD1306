#include "RH_Utility.h"
/*=================================================================================================
 > This part of code will never be compiled.
===================================================================================================*/
#if (1==0)
// Dummy Segment for Gussian Kernel

    int      kernel[1+2+3+4+5] = {0};
    uint16_t gus_kernel[9][9];

    int sigma = 0;

    double temp = 12.8;

    kernel[0]  = (uint16_t)(100 / (M_PI * temp));                       //[0][0]

    kernel[1]  = (uint16_t)(100 / (M_PI * temp) * exp(-1  / (temp)));   //[1][0]
    kernel[2]  = (uint16_t)(100 / (M_PI * temp) * exp(-2  / (temp)));   //[1][1]

    kernel[3]  = (uint16_t)(100 / (M_PI * temp) * exp(-4  / (temp)));   //[2][0]
    kernel[4]  = (uint16_t)(100 / (M_PI * temp) * exp(-5  / (temp)));   //[2][1]
    kernel[5]  = (uint16_t)(100 / (M_PI * temp) * exp(-8  / (temp)));   //[2][2]

    kernel[6]  = (uint16_t)(100 / (M_PI * temp) * exp(-9  / (temp)));   //[3][0]
    kernel[7]  = (uint16_t)(100 / (M_PI * temp) * exp(-10 / (temp)));   //[3][1]
    kernel[8]  = (uint16_t)(100 / (M_PI * temp) * exp(-13 / (temp)));   //[3][2]
    kernel[9]  = (uint16_t)(100 / (M_PI * temp) * exp(-18 / (temp)));   //[3][3]

    kernel[10] = (uint16_t)(100 / (M_PI * temp) * exp(-16 / (temp)));   //[4][0]
    kernel[11] = (uint16_t)(100 / (M_PI * temp) * exp(-17 / (temp)));   //[4][1]
    kernel[12] = (uint16_t)(100 / (M_PI * temp) * exp(-20 / (temp)));   //[4][2]
    kernel[13] = (uint16_t)(100 / (M_PI * temp) * exp(-25 / (temp)));   //[4][3]
    kernel[14] = (uint16_t)(100 / (M_PI * temp) * exp(-32 / (temp)));   //[4][4]

    sigma += kernel[0];        // 1
    sigma += (kernel[1]) << 2; // 4
    sigma += (kernel[2]) << 2; // 4

    sigma += (kernel[3]) << 2; // 4
    sigma += (kernel[4]) << 3; // 8
    sigma += (kernel[5]) << 2; // 4

    sigma += (kernel[6]) << 2; // 4
    sigma += (kernel[7]) << 3; // 8
    sigma += (kernel[8]) << 3; // 8
    sigma += (kernel[9]) << 2; // 4

    sigma += (kernel[10]) << 2; // 4
    sigma += (kernel[11]) << 3; // 8
    sigma += (kernel[12]) << 3; // 8
    sigma += (kernel[13]) << 3; // 8
    sigma += (kernel[14]) << 2; // 4

    int center   = ((9-1)>>1);

    for(int i = 0;i <= center;i++){
        for(int j = 0;j <= i;j++){
            gus_kernel[center + i][center + j] = kernel[i+j];
            gus_kernel[center + i][center - j] = kernel[i+j];
            gus_kernel[center - i][center + j] = kernel[i+j];
            gus_kernel[center - i][center - j] = kernel[i+j];
            gus_kernel[center + j][center + i] = kernel[i+j];
            gus_kernel[center + j][center - i] = kernel[i+j];
            gus_kernel[center - j][center + i] = kernel[i+j];
            gus_kernel[center - j][center - i] = kernel[i+j];
        }
    }
    sigma = 0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("[%3d]",gus_kernel[i][j]);
            sigma += gus_kernel[i][j];
        }
        printf("\n");
    }

    printf("sigma = %d\n",sigma);


// Dummy Segment for Digital Fourier Transform
void __DFT_Float(const float_t* src,float_t* dst,size_t dftLen){
    __ComplexFLOAT_t* pTmp = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
    memset(pTmp,0,dftLen*sizeof(__ComplexFLOAT_t));
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            pTmp[k].real += src[n]*cos(2*M_PI*k*n/dftLen);
            pTmp[k].imag += src[n]*sin(2*M_PI*k*n/dftLen);
        }
        dst[k] = sqrt(pTmp[k].real*pTmp[k].real+pTmp[k].imag*pTmp[k].imag);
        printf("%f + \tj*%f\n",pTmp[k].real,pTmp[k].imag);
    }
    __free(pTmp);
}


for(size_t k=0;k<((dftLen+2)>>1);k++){
    for(size_t n=0;n<dftLen;n++){
        pClx[k].real += src[n]*cos(2*M_PI*k*n/dftLen);
        pClx[k].imag += src[n]*sin(2*M_PI*k*n/dftLen);
    }
    if(dst_m != NULL)
        dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
    
    // Since the result of DFT is symmetrical, just copy the previous value.
    if(k!=0){
        pClx[dftLen-k].real =   pClx[k].real;
        pClx[dftLen-k].imag = - pClx[k].imag;
        if(dst_m != NULL)
            dst_m [dftLen-k]    =   dst_m[k];
    }
    
}


void __cDFT_Float(const __ComplexFLOAT_t* src,float_t* dst_m,__ComplexFLOAT_t* dst_c,size_t dftLen){
    __ComplexFLOAT_t* pClx = dst_c;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( pClx == NULL ){
        pClx = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
        if( pClx == NULL ){
            return;
        }
    }
    
    memset(pClx,0,dftLen*sizeof(__ComplexFLOAT_t));
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double temp = 2*M_PI*k*n/((double)(dftLen));
            pClx[k].real += src[n].real*cos(temp) + src[n].imag*sin(temp);
            pClx[k].imag += src[n].imag*cos(temp) - src[n].real*sin(temp);
        }
        if(dst_m != NULL)
            dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
    }
    
//    for(size_t k=0;k<dftLen;k++)
//        printf("| %.4f + j* %.4f | = \t%f\n",pClx[k].real,pClx[k].imag,dst_m[k]);
    if(dst_c == NULL)
        __free(pClx);
}


void __cIDFT_Float(const __ComplexFLOAT_t* src,float_t* dst_m,__ComplexFLOAT_t* dst_c,size_t dftLen){
    __ComplexFLOAT_t* pClx = dst_c;
    if( (dst_m == NULL&& dst_c == NULL) || src == NULL )
        return;
    if( pClx == NULL ){
        pClx = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
    }
    memset(pClx,0,dftLen*sizeof(__ComplexFLOAT_t));
    
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double temp = 2*M_PI*k*n/((double)(dftLen));
            pClx[k].real += src[n].real*cos(temp) - src[n].imag*sin(temp);
            pClx[k].imag += src[n].imag*cos(temp) + src[n].real*sin(temp);
        }
        pClx[k].real = pClx[k].real/(double)(dftLen);
        pClx[k].imag = pClx[k].imag/(double)(dftLen);
        if(dst_m != NULL)
            dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
        
    }
    
//    for(size_t k=0;k<dftLen;k++)
//        printf("| %f + \tj*%f | = \t%f\n",pClx[k].real,pClx[k].imag,dst_m[k]);
    if(dst_c == NULL)
        __free(pClx);
}

void __cDFT_Float(const __ComplexFLOAT_t* src,float_t* dst_m,__ComplexFLOAT_t* dst_c,size_t dftLen){
    __ComplexFLOAT_t* pClx = dst_c;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( pClx == NULL ){
        pClx = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
        if( pClx == NULL ){
            return;
        }
    }
    
    memset(pClx,0,dftLen*sizeof(__ComplexFLOAT_t));
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double temp = 2*M_PI*k*n/((double)(dftLen));
            pClx[k].real += src[n].real*cos(temp) + src[n].imag*sin(temp);
            pClx[k].imag += src[n].imag*cos(temp) - src[n].real*sin(temp);
        }
        if(dst_m != NULL)
            dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
    }
    
//    for(size_t k=0;k<dftLen;k++)
//        printf("| %.4f + j* %.4f | = \t%f\n",pClx[k].real,pClx[k].imag,dst_m[k]);
    if(dst_c == NULL)
        __free(pClx);
}




//Test for BIT_REVERSE!!!
const int BIT_SIZE = 32;  // 8 , 16 , 32
for(uint32_t x=0;x<(1<<BIT_SIZE);x++){
    uint32_t y = __swap_8BIT(x);
    for(int i=0;i<BIT_SIZE;i++){
        if( (((x>>i)&0x01) ^ ((y>>(BIT_SIZE-1-i))&0x01)) == 1 )
            printf("error\n");
    }
}


static void __insertSausageLine(int x1 ,int y1 ,int x2 ,int y2 ,size_t penSize ,Pixel_t penColor ,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_insertPointFunc){

    int x_offset = 0;
    int y_offset = 0;
    int x11=0,y11=0,x22=0,y22=0,x33=0,y33=0,x44=0,y44=0;

    __insertLine(x1,y1,x2,y2,penColor,pBufferInfo,Call_insertPointFunc);
    if(penSize > 1){

        //                -----------------------------------
        //              /       penSize * penSize * K^2
        // x_offset =  /    -------------------------------
        //           \/               K^2 + 1
        
        //                -----------------------------------
        //              /         penSize * penSize
        // y_offset =  /    -------------------------------
        //           \/               K^2 + 1

        
        switch(__Dir_Line(x1,y1,x2,y2)){
            case  0:
                x11 = x1; y11 = (int)(y1-(penSize>>1)+(penSize%2==0));
                x22 = x1; y22 = (int)(y1+(penSize>>1));
                x33 = x2; y33 = (int)(y2-(penSize>>1)+(penSize%2==0));
                x44 = x2; y44 = (int)(y2+(penSize>>1));
                break;
            case  1:
                x_offset = (int)lround(sqrt( ((y1-y2)*(y1-y2)*penSize*penSize/((x1-x2)*(x1-x2))) / (1.0*(y1-y2)*(y1-y2)/((x1-x2)*(x1-x2))+1) ));
                y_offset = (int)lround(sqrt( penSize*penSize/((y1-y2)*(y1-y2)/(1.0*(x1-x2)*(x1-x2))+1) ));
        
                x11 = x1+(x_offset>>1)-(x_offset%2==0); y11 = y1-(y_offset>>1);
                x22 = x1-(x_offset>>1)                ; y22 = y1+(y_offset>>1)-(y_offset%2==0);
                x33 = x2-(x_offset>>1)                ; y33 = y2+(y_offset>>1)-(y_offset%2==0);
                x44 = x2+(x_offset>>1)-(x_offset%2==0); y44 = y2-(y_offset>>1);
                break;
            case -1:
                x_offset = (int)lround(sqrt( ((y1-y2)*(y1-y2)*penSize*penSize/((x1-x2)*(x1-x2))) / (1.0*(y1-y2)*(y1-y2)/((x1-x2)*(x1-x2))+1) ));
                y_offset = (int)lround(sqrt( penSize*penSize/((y1-y2)*(y1-y2)/(1.0*(x1-x2)*(x1-x2))+1) ));
        
                x11 = x1+(x_offset>>1)                ; y11 = y1+(y_offset>>1)-(y_offset%2==0);
                x22 = x1-(x_offset>>1)+(x_offset%2==0); y22 = y1-(y_offset>>1)                ;
                x33 = x2-(x_offset>>1)+(x_offset%2==0); y33 = y2-(y_offset>>1)                ;
                x44 = x2+(x_offset>>1)                ; y44 = y2+(y_offset>>1)-(y_offset%2==0);
                break;
            case 65535:
                x11 = (int)(x1-(penSize>>1)                ); y11 = y1;
                x22 = (int)(x1+(penSize>>1)-(penSize%2==0)); y22 = y1;
                x33 = (int)(x2-(penSize>>1)                ); y33 = y2;
                x44 = (int)(x2+(penSize>>1)-(penSize%2==0)); y44 = y2;
                break;
        }
        (*Call_insertPointFunc)(x11,y11,penColor,pBufferInfo );
        (*Call_insertPointFunc)(x22,y22,penColor,pBufferInfo );
        (*Call_insertPointFunc)(x33,y33,penColor,pBufferInfo );
        (*Call_insertPointFunc)(x44,y44,penColor,pBufferInfo );

        __insertFilledQuadrilateral(  x11,y11, \
                                      x22,y22, \
                                      x33,y33, \
                                      x44,y44, \
                                      penColor  , \
                                      pBufferInfo,Call_insertPointFunc  );
        // GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
    }

    size_t tmp = (penSize>>1)-(penSize%2==0);
    penSize = 1;
    __insertFilledCircle(x1,y1,(int)tmp, penColor, pBufferInfo,Call_insertPointFunc);
    
    __insertFilledCircle(x2,y2,(int)tmp, penColor, pBufferInfo,Call_insertPointFunc);
    
}

#endif





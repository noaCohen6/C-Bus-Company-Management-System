#pragma once
#ifndef MACROS_H_
#define MACROS_H_


#define CHECK_FREE_COLSE_RETURN(ptr,fptr,fp) {if(!ptr){free(fptr);fclose(fp); return 0;}}
#define CHECK_COLSE_RETURN(ptr,fp) {if(!ptr){fclose(fp); return 0;}}
#define CALC_PRICE(price,dis) ((price) - ((price)*(dis)))

#endif
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

#include "draw.h"




void	drawRect(Img img, int px, int py, int h, int w, uint32_t c){
	for(int i = 0; i < h; i++){
		int y = i + py;
		if((y >= 0) && (y < img.h)){
			for(int j = 0; j < w; j++){
				int x = j + px;
				if((x >= 0) && (x < img.w)){
					int z = (y * img.w) + x;
					img.pix[z] = c;
				}
			}
		}
	}
}


void	drawVLine(Img img, int x, int y, int l, uint32_t c){
	if(l < 0){
		l = -l;
		for(int i = 0; i < l; i++){
			if(y < 0) return;
			int z = (y * img.w) + x;
			img.pix[z] = c;
			y--;
		}
	}else{
		for(int i = 0; i < l; i++){
			if(y >= img.h) return;
			int z = (y * img.w) + x;
			img.pix[z] = c;
			y++;
		}
	}
}


void	drawHLine(Img img, int x, int y, int l, uint32_t c){
	if(l < 0){
		l = -l;
		for(int i = 0; i < l; i++){
			if(x < 0) return;
			if(x < img.w){
				int z = (y * img.w) + x;
				img.pix[z] = c;
				x--;
			}
		}
	}else{
		for(int i = 0; i < l; i++){
			if(x >= img.w) return;
			if(x > 0){
				int z = (y * img.w) + x;
				img.pix[z] = c;
				x++;
			}
		}
	}
}



void drawView(View v, Img dst, Img src){
	int px = v.x - (dst.w >> v.zoom);
	int py = v.y - (dst.h >> v.zoom);

	for(int i = 0; i < dst.h; i++){
		int y = (i >> v.zoom) + py;
		if((y >= 0) && (y < src.h)){
			for(int j = 0; j < dst.w; j++){
				int x = (j >> v.zoom) + px;
				if((x >= 0) && (x < src.w)){
					int w = (x * src.w) + y;
					int z = (i * dst.w) + j;
					dst.pix[z] = src.pix[w];
				}
			}
		}
	}
}






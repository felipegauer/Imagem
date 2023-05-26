#include <stdio.h>
#include "lib_ppm.h"
void makeItBlackAndWhite(struct image_s *image);
void reverse(struct image_s *imageaux);
void upsidedown(struct image_s *imageaux);

void makeItBlackAndWhite(struct image_s *imageaux)
{
	struct image_s data;
	struct image_s *image = &data;
	new_ppm(image, imageaux->width, imageaux->height);

	for (int j = 0; j < image->height; j++)
	{
		for (int i = 0; i < image->width; i++)
		{
			int r = imageaux->pix[j * image->width + i].r;
			int g = imageaux->pix[j * image->width + i].g;
			int b = imageaux->pix[j * image->width + i].b;

			int avg = r * .299 + g * .587 + b * .114;

			image->pix[j * image->width + i].r = avg;
			image->pix[j * image->width + i].g = avg;
			image->pix[j * image->width + i].b = avg;
		}
	}
	write_ppm(".\\output\\BlackAndWhite.ppm", image);
	free_ppm(image);
}

void reverse(struct image_s *imageaux)
{
	struct image_s data;
	struct image_s *image = &data;
	new_ppm(image, imageaux->width, imageaux->height);

	for (int j = 0; j < image->height; j++)
		for (int i = 0; i < image->width / 2; i++)
		{
			image->pix[j * image->width + i]= imageaux->pix[j * image->width + (image->width - (i+1))];
			image->pix[j * image->width + (image->width - (i+1))] = imageaux->pix[j * image->width + i];
		}

	write_ppm(".\\output\\Reversed.ppm", image);
	free_ppm(image);
}

void upsidedown(struct image_s *imageaux)
{
	struct image_s data;
	struct image_s *image = &data;
	new_ppm(image, imageaux->width, imageaux->height);

	for (int j = 0; j < image->height/2; j++)
		for (int i = 0; i < image->width; i++)
		{
			image->pix[j * image->width + i]= imageaux->pix[(image->height - (j+1))* image->width + i];
			image->pix[(image->height - (j+1)) * image->width + i] = imageaux->pix[j * image->width + i];
		}

	write_ppm(".\\output\\UpsideDown.ppm", image);
	free_ppm(image);
}


int main()
{
	struct image_s data;
	struct image_s *image = &data;
	struct image_s data2;
	struct image_s *newImage = &data2;
	int i, j, r;
	int k = 0, x = 0, aumento = 1;

	r = read_ppm(".\\input\\lena.ppm", image);
	printf("deseja aumentar em quantas vezes a imagem?");
	scanf("%d", &aumento);

	new_ppm(newImage, image->width * aumento, image->height * aumento);

	if (r == 0)
	{
		printf("Old Image\n");
		printf("width: %d, height: %d\n", image->width, image->height);

		for (j = 0; j < image->height; j++)
		{
			for (i = 0; i < image->width; i++)
			{
				for (int a = 0; a < aumento; a++)
				{
					for (int b = 0; b < aumento; b++)
					{
						newImage->pix[(a + k) * newImage->width + (b + x)] = image->pix[j * image->width + i];
					}
				}
				x += aumento;
			}
			k += aumento - 1;
		}
		printf("New Image\n");
		printf("width: %d, height: %d\n", newImage->width, newImage->height);
		printf("Sucesso!\n");
		write_ppm(".\\output\\projetodeZOOM.ppm", newImage);

		makeItBlackAndWhite(newImage);
		reverse(newImage);
		upsidedown(newImage);
		free_ppm(image);
		free_ppm(newImage);
	}
	return 0;
}

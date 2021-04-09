#include "headers/cub3d.h"

void	ft_spriteLine(int x, int drawstart, int drawend, int color, t_rc *rc)
{
	int imgx;
	int imgy;
	int len = drawend - drawstart;
	int wle = 0;

	imgx = (int)(rc->txtn[4]->img_width * (rc->wallX - (int)rc->wallX));
	imgy = (int)(((rc->txtn[4]->img_height - 1) / (double)len) * wle);
	while (wle < len)
	{
		imgy = (int)(((rc->txtn[4]->img_height - 1) / (double)len) * wle);
		my_mlx_pixel_put(rc, x, drawstart, *(unsigned int*)get_pixel(rc->txtn[4], imgx, imgy));
		wle++;
		drawstart++;
	}
}

void	ft_Raycaster(t_rc *rc)
{
	int x = 0;
	rc->sprindex = -1;
	for(int x = 0; x < rc->pars->Rx; x++)
    {
		rc->cameraX = 2 * x / (double)(rc->pars->Rx) - 1;
		rc->rayDirX = rc->dirX + rc->planeX * rc->cameraX;
		rc->rayDirY = rc->dirY + rc->planeY * rc->cameraX;
		int mapX = (int)(rc->posX);
		int mapY = (int)(rc->posY);
		int sprite = 0;

		rc->deltaDistX = fabs(1 / rc->rayDirX);
		rc->deltaDistY = fabs(1 / rc->rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;

		rc->deltaDistX = (rc->rayDirY == 0) ? 0 : ((rc->rayDirX == 0) ? 1 : fabs(1 / rc->rayDirX));
		rc->deltaDistY = (rc->rayDirX == 0) ? 0 : ((rc->rayDirY == 0) ? 1 : fabs(1 / rc->rayDirY));

		if (rc->rayDirX < 0)
		{
			stepX = -1;
			rc->sideDistX = (rc->posX - mapX) * rc->deltaDistX;
		}
		else
		{
			stepX = 1;
			rc->sideDistX = (mapX + 1.0 - rc->posX) * rc->deltaDistX;
		}
		if (rc->rayDirY < 0)
		{
			stepY = -1;
			rc->sideDistY = (rc->posY - mapY) * rc->deltaDistY;
		}
		else
		{
			stepY = 1;
			rc->sideDistY = (mapY + 1.0 - rc->posY) * rc->deltaDistY;
		}
		while (hit == 0)
		{
			if (rc->sideDistX < rc->sideDistY)
			{
				rc->sideDistX += rc->deltaDistX;
				mapX += stepX;
				rc->side = 0;
				rc->sd = 0;
			}
			else
			{
				rc->sideDistY += rc->deltaDistY;
				mapY += stepY;
				rc->side = 1;
				rc->sd = 1;
			}
			if (rc->pars->map[mapX][mapY] == '1') hit = 1;
		}
		
		if (rc->side == 0)	perpWallDist = (mapX - rc->posX + (1 - stepX) / 2) / rc->rayDirX;
		else				perpWallDist = (mapY - rc->posY + (1 - stepY) / 2) / rc->rayDirY;
		int lineHeight = (int)(rc->pars->Ry / perpWallDist);

		int drawStart = -lineHeight / 2 + rc->pars->Ry / 2;
		int drawEnd = lineHeight / 2 + rc->pars->Ry / 2;

		if (rc->side == 0)
		{
			rc->wallX = rc->posY + perpWallDist * rc->rayDirY;
			if (rc->rayDirX > 0)
				rc->sd = 3;
		}
		else
		{
			rc->wallX = rc->posX + perpWallDist * rc->rayDirX;
			if (rc->rayDirY > 0)
				rc->sd = 2;
		}
		rc->zBuffer[x] = perpWallDist;
		ft_verLine(x, drawStart, drawEnd, rc);
	}
	ft_spritedata(rc);
	ft_sprite(rc);
	if (rc->save == 1)
		save_bmp("save.bmp", rc);
	mlx_put_image_to_window(rc->mlx, rc->win, rc->img, 0, 0);
}

int		main(int argc, char **argv)
{
	t_rc rc;
  	
	rc.txtn = wrmalloc(sizeof(t_img *) * 5);
	if (!rc.txtn)
		return (0);
	char **map;

	if (argc <= 0 || (rc.pars = ismapvalid(argv, argc)) == NULL)
	{
		printf("Error, map invalid\n");
		wrdestroy();
		return (0);
	}
	if (rc.pars->position == 'S')
	{
		rc.dirX = 1;
		rc.dirY = 0;
		rc.planeX = 0;
		rc.planeY = -0.66;
	}
	else if (rc.pars->position == 'N')
	{
		rc.dirX = -1;
		rc.dirY = 0;
		rc.planeX = 0;
		rc.planeY = 0.66;
	}
	else if (rc.pars->position == 'E')
	{
		rc.dirX = 0;
		rc.dirY = 1;
		rc.planeX = 0.66;
		rc.planeY = 0;
	}
	else
	{
		rc.dirX = 0;
		rc.dirY = -1;
		rc.planeX = -0.66;
		rc.planeY = 0;
	}

	if (argc == 3 && argv[2][0] == '-' && argv[2][1] == '-' && argv[2][2] == 's' && argv[2][3] == 'a' && argv[2][4] == 'v' && argv[2][5] == 'e')
		rc.save = 1;
	else
	{
		rc.save = 0;
	}

	if (rc.pars->Rx > 5120 / 2)
		rc.pars->Rx = 5120 / 2;
	if (rc.pars->Ry > 2880 / 2)
		rc.pars->Ry = 2880 / 2;

	rc.posX = rc.pars->yplayer + 0.5;
	rc.posY = rc.pars->xplayer + 0.5;

	int i;
	i = 0;

	while (rc.pars->map[i] != NULL)
	{
		i++;
	}
	rc.pars->hmap = i;
	i = 0;
	while (i < 5)
	{
		rc.txtn[i] = wrmalloc(sizeof(t_img));
		i++;
	}
	rc.mlx = mlx_init();
    rc.win = mlx_new_window(rc.mlx, rc.pars->Rx, rc.pars->Ry, "RayCaster");
	mlx_hook(rc.win, 2, 1L<<0, key_hook, &rc);
	mlx_hook(rc.win, 17, 0, ft_close, &rc);
	mlx_loop_hook(rc.mlx, key_hook, &rc);
	rc.img = mlx_new_image(rc.mlx, rc.pars->Rx, rc.pars->Ry);
    rc.addr = mlx_get_data_addr(rc.img, &rc.bits_per_pixel, &rc.line_length, &rc.endian);

	if (!(rc.txtn[0]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoNO, &rc.txtn[0]->img_width, &rc.txtn[0]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[0]->addr = mlx_get_data_addr(rc.txtn[0]->img, &rc.txtn[0]->bits_per_pixel, &rc.txtn[0]->line_length, &rc.txtn[0]->endian);
	
	if (!(rc.txtn[1]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoWE, &rc.txtn[1]->img_width, &rc.txtn[1]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[1]->addr = mlx_get_data_addr(rc.txtn[1]->img, &rc.txtn[1]->bits_per_pixel, &rc.txtn[1]->line_length, &rc.txtn[1]->endian);

	if (!(rc.txtn[2]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoEA, &rc.txtn[2]->img_width, &rc.txtn[2]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[2]->addr = mlx_get_data_addr(rc.txtn[2]->img, &rc.txtn[2]->bits_per_pixel, &rc.txtn[2]->line_length, &rc.txtn[2]->endian);

	if (!(rc.txtn[3]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoSO, &rc.txtn[3]->img_width, &rc.txtn[3]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[3]->addr = mlx_get_data_addr(rc.txtn[3]->img, &rc.txtn[3]->bits_per_pixel, &rc.txtn[3]->line_length, &rc.txtn[3]->endian);

	if (!(rc.txtn[4]->img = mlx_png_file_to_image(rc.mlx, rc.pars->pathtoS, &rc.txtn[4]->img_width, &rc.txtn[4]->img_height)))
	{
		printf("Error, img not found");
		return (0);
	}
	rc.txtn[4]->addr = mlx_get_data_addr(rc.txtn[4]->img, &rc.txtn[4]->bits_per_pixel, &rc.txtn[4]->line_length, &rc.txtn[4]->endian);
	
	ft_Raycaster(&rc);
	if (rc.save == 1)
		save_bmp("save.bmp", &rc);
	mlx_put_image_to_window(rc.mlx, rc.win, rc.img, 0, 0);
	mlx_loop(rc.mlx);
}
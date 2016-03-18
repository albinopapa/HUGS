/****************************************************************************************** 
 *	Chili DirectX Framework Version 14.03.22											  *	
 *	Game.cpp																			  *
 *	Copyright 2014 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "Game.h"
#include "TitleScreen.h"

Game::Game( HWND hWnd,KeyboardServer& kServer,MouseServer& mServer )
	:
	gfx( hWnd ),
	input( hWnd,mServer,kServer )
{
	srand(static_cast<unsigned int>(time(nullptr)));
	pScreen = std::make_unique<GameScreen>( gfx,input,this );
}

Game::~Game()
{
}

void Game::Go()
{
#if NDEBUG
	const float dt = timer.GetTimeSec();
	timer.StartWatch();
#else
	const float dt = 1.0f / 60.0f;
#endif

	UpdateModel( dt );
	gfx.BeginFrame();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{
	//input.di.GetPad().Update();

	try
	{
		pScreen->HandleInput();
		pScreen->Update( dt );
	}
	catch( Screen::Change )
	{
		UpdateModel( dt );
	}
}

void Game::ComposeFrame()
{
	auto p = Vec2( input.mouse.GetMouseX(),input.mouse.GetMouseY() );
	//pScreen->DrawPreBloom( gfx );
	const auto r = gfx.GetViewRegion();
	gfx.PutPixel( p.x + 32,p.y + 32,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 33,p.y + 32,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 34,p.y + 32,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 35,p.y + 32,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 32,p.y + 33,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 33,p.y + 33,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 34,p.y + 33,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 35,p.y + 33,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 32,p.y + 34,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 33,p.y + 34,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 34,p.y + 34,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 35,p.y + 34,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 32,p.y + 35,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 33,p.y + 35,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 34,p.y + 35,{ WHITE,255 } );
	//gfx.PutPixel( p.x + 35,p.y + 35,{ WHITE,255 } );

	for (int y = 32; y < 64; ++y)
	{
		gfx.DrawLineClip(Vec2(p.x - 32.0f, p.y + y), Vec2(p.x + 64.0f, p.y + y), { 255, 0, 255 }, r);
	}
	/*for (int y = 0; y < gfx.GetHeight(); ++y)
	{
		for (int x = 0; x < gfx.GetWidth(); ++x)
		{
			unsigned char red = static_cast<unsigned char>(rand() % 255);
			unsigned char green = static_cast<unsigned char>(rand() % 255);
			unsigned char blue = static_cast<unsigned char>(rand() % 255);

			gfx.PutPixel(x, y, { red, green, blue});
		}
	}*/

	gfx.ProcessBloom();
	//pScreen->DrawPostBloom( gfx );
}
#include "ZombieArena.h"


int createBackground(VertexArray& rVA, IntRect arena) {

    // How big is each tile/texture
	const int TILE_SIZE = 50;
	const int TILE_TYPES = 3;
	const int VERTS_IN_QUAD = 4;
	int worldWidth = arena.width / TILE_SIZE;
	int worldHeight = arena.height / TILE_SIZE;
	// What type of primitive are we using?
	rVA.setPrimitiveType(Quads);
	// Set the size of the vertex array
	rVA.resize(worldWidth * worldHeight * VERTS_IN_QUAD);
	// Start at the beginning of the vertex array
	int currentVertex = 0;

	for (int w = 0; w < worldWidth; w++)
	{
		for (int h = 0; h < worldHeight; h++)
		{
			// Position each vertex in the current quad
			rVA[currentVertex + 0].position =
				Vector2f(w * TILE_SIZE, h * TILE_SIZE);

			rVA[currentVertex + 1].position =
				Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);

			rVA[currentVertex + 2].position =
				Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE)
					+ TILE_SIZE);
			rVA[currentVertex + 3].position =
				Vector2f((w * TILE_SIZE), (h * TILE_SIZE)
					+ TILE_SIZE);

			// Define the position in the Texture for current quad
            // Either grass, stone, bush or wall
			if (h == 0 || h == worldHeight - 1 ||
				w == 0 || w == worldWidth - 1)
			{
				
				// Use the wall texture
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, 0 + TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 1].texCoords =
					Vector2f(TILE_SIZE, 0 +
						TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 2].texCoords =
					Vector2f(TILE_SIZE, TILE_SIZE +
						TILE_TYPES * TILE_SIZE);

				rVA[currentVertex + 3].texCoords =
					Vector2f(0, TILE_SIZE +
						TILE_TYPES * TILE_SIZE);
			}
			else
			{				
				// Use a random floor texture
				srand((int)time(0) + h * w - h);
				int mOrG = (rand() % TILE_TYPES);
				int verticalOffset = mOrG * TILE_SIZE;
				rVA[currentVertex + 0].texCoords =
					Vector2f(0, 0 + verticalOffset);

			    // Position ready for the next four vertices
		     	currentVertex = currentVertex + VERTS_IN_QUAD;
		    	rVA[currentVertex + 1].texCoords =
				Vector2f(TILE_SIZE, 0 + verticalOffset);

			    rVA[currentVertex + 2].texCoords =
				Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);

		     	rVA[currentVertex + 3].texCoords =
				Vector2f(0, TILE_SIZE + verticalOffset);
			}
		}
	}
	
	return TILE_SIZE;

}

Zombie* createHorde(int numZombies, IntRect arena)
{
	Zombie* zombies = new Zombie[numZombies];
	int maxY = arena.height - 20;
	int minY = arena.top + 20;
	int maxX = arena.width - 20;
	int minX = arena.left + 20;

	for (int i = 0; i < numZombies; i++)
	{
		// Which side should the zombie spawn
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;
		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		}

		// Bloater, crawler or runner
		srand((int)time(0) * i * 2);
		int type = (rand() % 3);
		// Spawn the new zombie into the array
		zombies[i].spawn(x, y, type, i);
	}

	return zombies;
}
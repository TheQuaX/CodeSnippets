package gameoflife;

import java.awt.Graphics;
import java.util.Random;

public class Game {

	private Cell[][] cells;
	private int width = Form.winSize / Cell.size;
	private int height = Form.winSize / Cell.size;

	private Random randomState;

	// Initialise cells
	public Game() {

		randomState = new Random();
		cells = new Cell[width][height];

		// LOOP through all cells
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {

				// Create cells
				cells[x][y] = new Cell(x, y);
				cells[x][y].setState(randomState.nextBoolean());

			}
		}

	}

	// update method
	public void update() {

		// LOOP through all cells
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {

				// Check neighbour-cells

				// Left Side (horizontal left)
				int hl = x - 1;
				// fixed the - index of the array
				if (hl < 0) {
					hl = width - 1;
				}

				// Upper Side (vertical up)
				int vu = y - 1;
				// fixed the - index of the array
				if (vu < 0) {
					vu = height - 1;
				}

				// Right Side (horizontal right)
				int hr = (x + 1) % width;

				// Bottom Side (vertical down)
				int vd = (y + 1) % height;

				// countingNeigbours
				int livingNeighbours = 0;

				// Check them all
				
				//example: top-left
				if (cells[hl][vu].isState()) {
					livingNeighbours++;
				}
				
				//middle_left
				if (cells[hl][y].isState()) {
					livingNeighbours++;
				}
				if (cells[hl][vd].isState()) {
					livingNeighbours++;
				}
				if (cells[x][vu].isState()) {
					livingNeighbours++;
				}
				if (cells[x][vd].isState()) {
					livingNeighbours++;
				}
				if (cells[hr][vu].isState()) {
					livingNeighbours++;
				}
				if (cells[hr][y].isState()) {
					livingNeighbours++;
				}
				if (cells[hr][vd].isState()) {
					livingNeighbours++;
				}

				// Rules
				if (livingNeighbours < 2 || livingNeighbours > 3) {
					cells[x][y].setbool_nextRound(false);
				}

				else if (livingNeighbours == 3) {
					cells[x][y].setbool_nextRound(true);
				}

			}
		}

		// LOOP through all cells again
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {

				// nextround call
				cells[x][y].nextRound();

			}
		}
	}

	// Draw the Cell
	public void drawCell(Graphics g) {

		// LOOP through all cells
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {

				cells[x][y].draw(g);

			}
		}
	}

}

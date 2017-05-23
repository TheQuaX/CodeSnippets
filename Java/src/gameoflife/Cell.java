package gameoflife;

import java.awt.Color;
import java.awt.Graphics;

public class Cell {

	// Variables
	// Position
	private int x;
	private int y;

	// state 0 = dead, 1 = alive
	private boolean state;

	// NextRound
	private boolean bool_nextRound;
	// Cell Size
	static int size = 3;

	// Constructor of Cell
	public Cell(int x, int y) {

		this.x = x;
		this.y = y;

	}

	// getter and setter
	public boolean isState() {
		return state;
	}

	// getter and setter
	public void setState(boolean state) {
		this.state = state;
	}

	// set bool_nextRound
	public void setbool_nextRound(boolean bool_nextRound) {
		this.bool_nextRound = bool_nextRound;
	}

	// nextRound method
	public void nextRound() {

		state = bool_nextRound;
	}

	// Draw Cell
	public void draw(Graphics g) {

		g.setColor(Color.BLACK);
		// g.drawRect(x * size, y * size, size, size);
		if (state) {
			g.setColor(Color.black);
		} else {
			g.setColor(Color.lightGray);
		}
		g.fillRect(x * size, y * size, size, size);

	}

}

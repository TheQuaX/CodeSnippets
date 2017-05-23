package gameoflife;

import java.awt.Graphics;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Form extends JFrame {

	// screenvar
	private Screen s;

	// Gamevar
	private Game game;

	// WindowSize
	static int winSize = 800;

	// Update ticker
	private float WAIT = 0.1f;

	private float lastupdate;

	// Window
	public Form() {

		// Setting up the window form

		// Make the window borderless
		setExtendedState(MAXIMIZED_BOTH);

		// set the operation to close when pressing the X
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// set the title
		setTitle("Game of Life - Alexander Mordas");

		// set the size to 400 x 400
		setSize(winSize, winSize);

		// make the window nonresizable
		setResizable(false);

		// Open the window in the center of the screen
		setLocationRelativeTo(null);

		// Setting the visibility to true
		setVisible(true);

		// create new game
		game = new Game();

		// create new Screen
		s = new Screen();
		s.setBounds(0, 0, winSize, winSize);
		add(s);
	}

	// Update
	public void update(float deltaframetime) {

		// add lastupdate to deltaframetime
		lastupdate += deltaframetime;

		// if lastupdate is > then the pause time then update
		if (lastupdate > WAIT) {

			// Call game.update
			game.update();

			// setting lastupdate to zero
			lastupdate = 0;

		}

	}

	// Refresh Renderer
	public void repaint() {
		s.repaint();
	}

	// Drawableobject
	private class Screen extends JLabel {

		public void paintComponent(Graphics g) {
			super.paintComponent(g);

			game.drawCell(g);
		}

	}
}

package gameoflife;

public class Main {

	public static void main(String[] args) {

		Form GameWindow = new Form();

		// last frame value
		long lastFrame = System.currentTimeMillis();

		// Renderer Loop
		while (true) {

			// current time at this moment
			long thisFrame = System.currentTimeMillis();

			// calculate the difference
			float deltaframetime = (float) ((thisFrame - lastFrame) / 1000.0);

			lastFrame = thisFrame;

			GameWindow.update(deltaframetime);
			GameWindow.repaint();

			try {
				Thread.sleep(10);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}

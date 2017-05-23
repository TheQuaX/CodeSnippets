using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Net;
using System.Text.RegularExpressions;


namespace EAN_DATA_GRABBER_V2
{
    public partial class UserFormMain : Form
    {
        public UserFormMain()
        {
            InitializeComponent();                       
        }

        //Variablen deklarieren
        string @InputFilePath = "";
        string @OutputFilePath = "";
        string OutputName = "\\";
        string currentean = "";
        string errorkriterium = "<h1 style=\"margin - top: 65px; font - size: 26px\">There is no such barcode or product name in our database.<h1>";
        string kriterium1 = "<h4>(.*)</h4>";
        string kriterium2 = "Category: <span class=\"format-text\">(.*) </span></div><div class=\"format-label\">";
        string kriterium3 = "Manufacturer: <span class=\"format-text\">(.*) </span>";
        string kriterium4 = "Amazon.de                                    - &euro;(.*)                                  ";



        private void buttonInputSet_Click(object sender, EventArgs e)
        {
            OpenFileDialog InputPath = new OpenFileDialog();
            InputPath.Filter = "txt|*.txt";
            if (InputPath.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textBoxInputPath.Text = InputPath.FileName;
                InputFilePath = textBoxInputPath.Text;
            }

            //Aktiviere Startbutton wenn Input & Output nicht NULL sind
            if (textBoxInputPath.Text != "" && textBoxOutputPath.Text != "" && textBoxOutputName.Text != "") { buttonStartProg.Enabled = true; }
        }

        private void buttonOutputSet_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog OutputPath = folderBrowserDialogOutput;
            if (OutputPath.ShowDialog() == System.Windows.Forms.DialogResult.OK) {
                textBoxOutputPath.Text = OutputPath.SelectedPath;
                OutputFilePath = textBoxOutputPath.Text;
            }

            //Aktiviere Startbutton wenn Input & Output nicht NULL sind
            if (textBoxInputPath.Text != "" && textBoxOutputPath.Text != "") { buttonStartProg.Enabled = true; }
        }

        //Button "START" wurde gedrückt
        private void buttonStartProg_Click(object sender, EventArgs e)
        {
            //Outputname hinzufügen
            @OutputName = "\\" + textBoxOutputName.Text;

            //Label anpassen
            labelStatusText.Text = "running!";

            //Button deaktivieren
            buttonStartProg.Enabled = false;



            //Ladebalken setzen
            progressBarStatus.Maximum = System.IO.File.ReadAllLines(@InputFilePath).Length;
            System.Console.Write("Länge der Bar geändert auf: "+ progressBarStatus.Maximum);

            //Input und Output festlegen
            StreamReader ReadInput = new StreamReader(@InputFilePath);
            StreamWriter WriteOutput = new StreamWriter(@OutputFilePath + OutputName+".txt");

            //Solange Zeilen vorhanden, setze Quellcode auf null und lese ihn anschließend ein
            while ((currentean = ReadInput.ReadLine()) != null) {
                string Quellcode = "";
                Quellcode = getHTML(currentean);
                

                //Errorabfrage
                foreach (Match abbruch in Regex.Matches(Quellcode, errorkriterium)) {
                    WriteOutput.WriteLine("Fehler!\n");
                }

                //alle anderen Kriterien
                foreach (Match krit_one in Regex.Matches(Quellcode, kriterium1)) {
                    foreach (Match krit_two in Regex.Matches(Quellcode, kriterium2)) {
                        foreach (Match krit_three in Regex.Matches(Quellcode, kriterium3)) {
                            foreach (Match krit_four in Regex.Matches(Quellcode, kriterium4)) {
                                WriteOutput.WriteLine(currentean+";"+krit_one.Groups[1].Value + ";" + krit_two.Groups[1].Value + ";" + krit_three.Groups[1].Value + ";" + krit_four.Groups[1].Value + ";");
                               
                            }
                        }
                    }
                }
                progressBarStatus.Value += 1;


            }

            ReadInput.Close();
            labelStatusText.Text = "Job done!";
            buttonStartProg.Enabled = true;
            Console.Beep();


            //ganz am Ende ausführen!
            WriteOutput.Close();
        }



        public string getHTML(string ean)
        {
            string server = "SERVERIP";
            //Anfrage an die Übergebene URL starten
            HttpWebRequest request = (HttpWebRequest)HttpWebRequest.Create(server + ean);

            //Antwort-Objekt erstellen
            HttpWebResponse response = (HttpWebResponse)request.GetResponse();

            //Antwort Stream an Streamreader übergeben
            StreamReader sr = new StreamReader(response.GetResponseStream());

            //Antwort (HTML Code) auslesen
            string html = sr.ReadToEnd();

            //Streamreader und Webanfrage schließen
            sr.Close();
            response.Close();

            //Quellcode zurückgeben
            return html;
        }
    }



}

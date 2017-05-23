//C# ct-Savesystem by Alexander Mordas

using System.IO;

//VARIABLES TO SAVE
int score;
string name;

//SAVING
//Textwriter SAVING
TextWriter saving = new StreamWriter("saving.xms");

saving.WriteLine("score = " + score);
saving.WriteLine("name = " + name);
saving.Close();


#region LOADING
//LOADING
//Setting up dictionary
var dic = File.ReadAllLines("saving.xms")
                    .Select(l => l.Split(new[] { '=' }))
                    .ToDictionary(s => s[0].Trim(), s => s[1].Trim());

//reading lines
string saved_score = dic["score"];
string saved_name = dic["name"];

//converting to type
score = Convert.ToInt32(saved_score);
name = saved_name;
#endregion
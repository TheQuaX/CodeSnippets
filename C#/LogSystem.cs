            try
            {
                int zero = 0;
                int fail;
                fail = 7 / zero;

            }
            catch (Exception ex)
            {
                using (System.IO.StreamWriter file = new System.IO.StreamWriter(@"test.log", true))
                {
                    string log = ex.ToString();
                    file.WriteLine($"{ DateTime.Now.ToString()}: {log}");
                }
            }
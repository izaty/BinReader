using System;
using System.IO;

class MyBinaryReader {
    public int aaa;
    public int bbb;
    public double[] fd;

    public MyBinaryReader() {}

    public void read(String filePath) {
        int i, j;


        using (FileStream fis = new FileStream(filePath,
            FileMode.Open, FileAccess.Read)) {

            byte[] bytes = new byte[fis.Length];

            fis.Read(bytes, 0, sizeof(int));
            aaa = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            bbb = BitConverter.ToInt32(bytes, 0);
            fd = new double[13];
            for (i = 0; i < 13; i++) {
                fis.Read(bytes, 0, sizeof(double));
                fd[i] = BitConverter.ToDouble(bytes, 0);
            }

        }

    }

    static int Main() {
        string[] args = Environment.GetCommandLineArgs();
        if (args.Length != 2) {
            Console.WriteLine("Usage: {0} filename", args[0]);
            return -999;
        }
        try {
            MyBinaryReader br = new MyBinaryReader();
            br.read(args[1]);
        } catch (IOException ex) {
            Console.WriteLine(ex.ToString());
            return -1;
        }

        return 0;
    }
}

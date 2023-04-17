using System;
using System.IO;

class MyBinaryReader
{
    public int h1s;
    public int magic;
    public int h1e;
    public int h2s;
    public byte[] fname;
    public int h2e;
    public int h3s;
    public byte[] cdate;
    public byte[] mdate;
    public byte[] author;
    public int h3e;
    public int h4s;
    public byte[] commen;
    public int h4e;
    public int h5s;
    public int iresta;
    public int nstep;
    public int minit;
    public int mfinl;
    public int mintv;
    public int h5e;
    public int h6s;
    public float dt;
    public int nsbloc;
    public int iensem;
    public int itemp;
    public int ipres;
    public float rcut;
    public int h6e;
    public int h7s;
    public int natom0;
    public int kmol;
    public int nummon;
    public int numthe;
    public int numrsv;
    public int numblk;
    public int h7e;
    public int h8s;
    public byte[][] chamol;
    public int[] idynam;
    public int[] nummol0;
    public int[] numatm;
    public int[] numbon;
    public int[] kindat;
    public int h8e;
    public int h9s;
    public int[][] kinatm;
    public byte[][][] chatom;
    public byte[][][] atmkid;
    public float[][] cmass;
    public float[][] charge;
    public int h9e;

    public MyBinaryReader() { }

    public void read(String filePath)
    {
        int i, j, k, l;


        using (FileStream fis = new FileStream(filePath,
            FileMode.Open, FileAccess.Read))
        {

            byte[] bytes = new byte[fis.Length];

            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h1s = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            magic = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h1e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h2s = BitConverter.ToInt32(bytes, 0);
            fname = new byte[256];
            fis.Read(fname, 0, 256);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h2e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h3s = BitConverter.ToInt32(bytes, 0);
            cdate = new byte[8];
            fis.Read(cdate, 0, 8);
            mdate = new byte[8];
            fis.Read(mdate, 0, 8);
            author = new byte[30];
            fis.Read(author, 0, 30);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h3e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h4s = BitConverter.ToInt32(bytes, 0);
            commen = new byte[80];
            fis.Read(commen, 0, 80);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h4e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h5s = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            iresta = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            nstep = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            minit = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            mfinl = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            mintv = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h5e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h6s = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(float));
            Array.Reverse(bytes, 0, sizeof(float));
            dt = BitConverter.ToSingle(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            nsbloc = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            iensem = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            itemp = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            ipres = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(float));
            Array.Reverse(bytes, 0, sizeof(float));
            rcut = BitConverter.ToSingle(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h6e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h7s = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            natom0 = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            kmol = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            nummon = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            numthe = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            numrsv = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            numblk = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h7e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h8s = BitConverter.ToInt32(bytes, 0);
            chamol = new byte[kmol][];
            for (i = 0; i < kmol; i++)
            {
                chamol[i] = new byte[16];
                fis.Read(chamol[i], 0, 16);
            }
            idynam = new int[kmol];
            for (i = 0; i < kmol; i++)
            {
                fis.Read(bytes, 0, sizeof(int));
                Array.Reverse(bytes, 0, sizeof(int));
                idynam[i] = BitConverter.ToInt32(bytes, 0);
            }
            nummol0 = new int[kmol];
            for (i = 0; i < kmol; i++)
            {
                fis.Read(bytes, 0, sizeof(int));
                Array.Reverse(bytes, 0, sizeof(int));
                nummol0[i] = BitConverter.ToInt32(bytes, 0);
            }
            numatm = new int[kmol];
            for (i = 0; i < kmol; i++)
            {
                fis.Read(bytes, 0, sizeof(int));
                Array.Reverse(bytes, 0, sizeof(int));
                numatm[i] = BitConverter.ToInt32(bytes, 0);
            }
            numbon = new int[kmol];
            for (i = 0; i < kmol; i++)
            {
                fis.Read(bytes, 0, sizeof(int));
                Array.Reverse(bytes, 0, sizeof(int));
                numbon[i] = BitConverter.ToInt32(bytes, 0);
            }
            kindat = new int[kmol];
            for (i = 0; i < kmol; i++)
            {
                fis.Read(bytes, 0, sizeof(int));
                Array.Reverse(bytes, 0, sizeof(int));
                kindat[i] = BitConverter.ToInt32(bytes, 0);
            }
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h8e = BitConverter.ToInt32(bytes, 0);
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h9s = BitConverter.ToInt32(bytes, 0);
            kinatm = new int[kmol][];
            for (i = 0; i < kmol; i++)
            {
                kinatm[i] = new int[numatm[i]];
                for (j = 0; j < numatm[i]; j++)
                {
                    fis.Read(bytes, 0, sizeof(int));
                    Array.Reverse(bytes, 0, sizeof(int));
                    kinatm[i][j] = BitConverter.ToInt32(bytes, 0);
                }
            }
            chatom = new byte[kmol][][];
            for (i = 0; i < kmol; i++)
            {
                chatom[i] = new byte[numatm[i]][];
                for (j = 0; j < numatm[i]; j++)
                {
                    chatom[i][j] = new byte[2];
                    fis.Read(chatom[i][j], 0, 2);
                }
            }
            atmkid = new byte[kmol][][];
            for (i = 0; i < kmol; i++)
            {
                atmkid[i] = new byte[numatm[i]][];
                for (j = 0; j < numatm[i]; j++)
                {
                    atmkid[i][j] = new byte[2];
                    fis.Read(atmkid[i][j], 0, 2);
                }
            }
            cmass = new float[kmol][];
            for (i = 0; i < kmol; i++)
            {
                cmass[i] = new float[numatm[i]];
                for (j = 0; j < numatm[i]; j++)
                {
                    fis.Read(bytes, 0, sizeof(float));
                    Array.Reverse(bytes, 0, sizeof(float));
                    cmass[i][j] = BitConverter.ToSingle(bytes, 0);
                }
            }
            charge = new float[kmol][];
            for (i = 0; i < kmol; i++)
            {
                charge[i] = new float[numatm[i]];
                for (j = 0; j < numatm[i]; j++)
                {
                    fis.Read(bytes, 0, sizeof(float));
                    Array.Reverse(bytes, 0, sizeof(float));
                    charge[i][j] = BitConverter.ToSingle(bytes, 0);
                }
            }
            fis.Read(bytes, 0, sizeof(int));
            Array.Reverse(bytes, 0, sizeof(int));
            h9e = BitConverter.ToInt32(bytes, 0);

        }

    }

    public void write(String filePath)
    {
        int i, j, k, l;


        using (FileStream fos = new FileStream(filePath,
            FileMode.Create, FileAccess.Write))
        {

            byte[] bytes = null;

            bytes = BitConverter.GetBytes(h1s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(magic);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h1e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h2s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            fos.Write(fname, 0, 256);
            bytes = BitConverter.GetBytes(h2e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h3s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            fos.Write(cdate, 0, 8);
            fos.Write(mdate, 0, 8);
            fos.Write(author, 0, 30);
            bytes = BitConverter.GetBytes(h3e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h4s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            fos.Write(commen, 0, 80);
            bytes = BitConverter.GetBytes(h4e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h5s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(iresta);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(nstep);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(minit);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(mfinl);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(mintv);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h5e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h6s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(dt);
            Array.Reverse(bytes, 0, sizeof(float));
            fos.Write(bytes, 0, sizeof(float));
            bytes = BitConverter.GetBytes(nsbloc);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(iensem);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(itemp);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(ipres);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(rcut);
            Array.Reverse(bytes, 0, sizeof(float));
            fos.Write(bytes, 0, sizeof(float));
            bytes = BitConverter.GetBytes(h6e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h7s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(natom0);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(kmol);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(nummon);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(numthe);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(numrsv);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(numblk);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h7e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h8s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            for (i = 0; i < kmol; i++)
            {
                fos.Write(chamol[i], 0, 16);
            }
            for (i = 0; i < kmol; i++)
            {
                bytes = BitConverter.GetBytes(idynam[i]);
                Array.Reverse(bytes, 0, sizeof(int));
                fos.Write(bytes, 0, sizeof(int));
            }
            for (i = 0; i < kmol; i++)
            {
                bytes = BitConverter.GetBytes(nummol0[i]);
                Array.Reverse(bytes, 0, sizeof(int));
                fos.Write(bytes, 0, sizeof(int));
            }
            for (i = 0; i < kmol; i++)
            {
                bytes = BitConverter.GetBytes(numatm[i]);
                Array.Reverse(bytes, 0, sizeof(int));
                fos.Write(bytes, 0, sizeof(int));
            }
            for (i = 0; i < kmol; i++)
            {
                bytes = BitConverter.GetBytes(numbon[i]);
                Array.Reverse(bytes, 0, sizeof(int));
                fos.Write(bytes, 0, sizeof(int));
            }
            for (i = 0; i < kmol; i++)
            {
                bytes = BitConverter.GetBytes(kindat[i]);
                Array.Reverse(bytes, 0, sizeof(int));
                fos.Write(bytes, 0, sizeof(int));
            }
            bytes = BitConverter.GetBytes(h8e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            bytes = BitConverter.GetBytes(h9s);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));
            for (i = 0; i < kmol; i++)
            {
                for (j = 0; j < numatm[i]; j++)
                {
                    bytes = BitConverter.GetBytes(kinatm[i][j]);
                    Array.Reverse(bytes, 0, sizeof(int));
                    fos.Write(bytes, 0, sizeof(int));
                }
            }
            for (i = 0; i < kmol; i++)
            {
                for (j = 0; j < numatm[i]; j++)
                {
                    fos.Write(chatom[i][j], 0, 2);
                }
            }
            for (i = 0; i < kmol; i++)
            {
                for (j = 0; j < numatm[i]; j++)
                {
                    fos.Write(atmkid[i][j], 0, 2);
                }
            }
            for (i = 0; i < kmol; i++)
            {
                for (j = 0; j < numatm[i]; j++)
                {
                    bytes = BitConverter.GetBytes(cmass[i][j]);
                    Array.Reverse(bytes, 0, sizeof(float));
                    fos.Write(bytes, 0, sizeof(float));
                }
            }
            for (i = 0; i < kmol; i++)
            {
                for (j = 0; j < numatm[i]; j++)
                {
                    bytes = BitConverter.GetBytes(charge[i][j]);
                    Array.Reverse(bytes, 0, sizeof(float));
                    fos.Write(bytes, 0, sizeof(float));
                }
            }
            bytes = BitConverter.GetBytes(h9e);
            Array.Reverse(bytes, 0, sizeof(int));
            fos.Write(bytes, 0, sizeof(int));

        }

    }

    static int Main()
    {
        string[] args = Environment.GetCommandLineArgs();
        if (args.Length != 3)
        {
            Console.WriteLine("Usage: {0} inputfilename outputfilename", args[0]);
            return -999;
        }
        try
        {
            MyBinaryReader br = new MyBinaryReader();
            br.read(args[1]);
            int i, j;
            for (i = 0; i < br.kmol; i++)
            {
                for (j = 0; j < br.numatm[i]; j++)
                {
                    Console.WriteLine("charge[{0}][{1}] = {2}", i, j, br.charge[i][j]);
                }
            }
        }
        catch (IOException ex)
        {
            Console.WriteLine(ex.ToString());
            return -1;
        }

        return 0;
    }
}

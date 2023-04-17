using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace CSharpTest
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 1) {
                Console.WriteLine("Usage: MyBinaryReader filename");
                return;
                //return -999;
            }
            //try {
                MyBinaryReader br = new MyBinaryReader();
                br.read(args[0]);
            //} catch () {
                //return -1;
            //}

            //return 0;
        }
    }

    class MyBinaryReader
    {
        public MyBinaryReader() { }

        byte[] readBytes(FileStream fs, int size, int count)
        {
            int total = size * count;
            byte[] bytes = new byte[total];

            int numBytes = fs.Read(bytes, 0, total);
            for (int i = 0; i < count; i++) {
                Array.Reverse(bytes, i * size, size);
            }

            return bytes;
        }

        byte[] reverse(byte[] bytes, int nsize)
        {
            if (nsize > 0)
            {
                int i;
                byte[] temp = new byte[nsize];
                for (i = 0; i < nsize; i++)
                {
                    temp[i] = bytes[nsize - i - 1];
                }
                for (i = 0; i < nsize; i++)
                {
                    bytes[i] = temp[i];
                }
            }
            return bytes;
        }

        public void read(String filePath)
        {
            int i0, i1, i2, i3;

            int h1s;
            int magic;
            int h1e;
            int h2s;
            char[] fname;
            int h2e;
            int h3s;
            char[] cdate;
            char[] mdate;
            char[] author;
            int h3e;
            int h4s;
            char[] commen;
            int h4e;
            int h5s;
            int iresta;
            int nstep;
            int minit;
            int mfinl;
            int mintv;
            int h5e;
            int h6s;
            float dt;
            int nsbloc;
            int iensem;
            int itemp;
            int ipres;
            float rcut;
            int h6e;
            int h7s;
            int natom0;
            int kmol;
            int nummon;
            int numthe;
            int numrsv;
            int numblk;
            int h7e;
            int h8s;
            char[][] chamol;
            int[] idynam;
            int[] nummol0;
            int[] numatm;
            int[] numbon;
            int[] kindat;
            int h8e;
            int h9s;
            int[][] kinatm;
            char[][][] chatom;
            char[][][] atmkid;
            float[][] cmass;
            float[][] charge;
            int h9e;

            using (FileStream fs = new FileStream(filePath,
                FileMode.Open, FileAccess.Read)) {

                byte[] bytes;

                bytes = readBytes(fs, sizeof(int), 1);
                h1s = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h1s);

                bytes = readBytes(fs, sizeof(int), 1);
                magic = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(magic);

                bytes = readBytes(fs, sizeof(int), 1);
                h1e = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h1e);

                bytes = readBytes(fs, sizeof(int), 1);
                h2s = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h2s);

                    fname = new char[256];
                    numBytesRet += fis.Read(bytes, 0, 256);// sizeof(char) NG

                bytes = readBytes(fs, sizeof(int), 1);
                h2e = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h2e);

                bytes = readBytes(fs, sizeof(int), 1);
                h3s = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h3s);

                    cdate = new char[8];
                    for (i0 = 0; i0 < 8; i0++) {
                        numBytesRet += fis.Read(bytes, 0, sizeof(char));
                        cdate[i0] = BitConverter.ToChar(bytes, 0);
                    }
                    mdate = new char[8];
                    for (i0 = 0; i0 < 8; i0++) {
                        numBytesRet += fis.Read(bytes, 0, sizeof(char));
                        mdate[i0] = BitConverter.ToChar(bytes, 0);
                    }
                    author = new char[30];
                    for (i0 = 0; i0 < 30; i0++) {
                        numBytesRet += fis.Read(bytes, 0, sizeof(char));
                        author[i0] = BitConverter.ToChar(bytes, 0);
                    }

                bytes = readBytes(fs, sizeof(int), 1);
                h3e = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h3e);

                bytes = readBytes(fs, sizeof(int), 1);
                h4s = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h4s);

                    commen = new char[80];
                    for (i0 = 0; i0 < 80; i0++) {
                        numBytesRet += fis.Read(bytes, 0, sizeof(char));
                        commen[i0] = BitConverter.ToChar(bytes, 0);
                    }

                bytes = readBytes(fs, sizeof(int), 1);
                h4e = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h4e);

                bytes = readBytes(fs, sizeof(int), 1);
                h5s = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h5s);

                bytes = readBytes(fs, sizeof(int), 1);
                iresta = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(iresta);

                bytes = readBytes(fs, sizeof(int), 1);
                nstep = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(nstep);

                bytes = readBytes(fs, sizeof(int), 1);
                minit = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(minit);

                bytes = readBytes(fs, sizeof(int), 1);
                mfinl = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(mfinl);

                bytes = readBytes(fs, sizeof(int), 1);
                mintv = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(mintv);

                bytes = readBytes(fs, sizeof(int), 1);
                h5e = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h5e);

                bytes = readBytes(fs, sizeof(int), 1);
                h6s = BitConverter.ToInt32(bytes, 0);
                Console.WriteLine(h6s);

                bytes = readBytes(fs, sizeof(float), 1);
                dt = BitConverter.ToSingle(bytes, 0);
                Console.WriteLine(dt);

                nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    nsbloc = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    iensem = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    itemp = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    ipres = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    rcut = BitConverter.ToSingle(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h6e = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h7s = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    natom0 = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    kmol = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    nummon = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    numthe = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    numrsv = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    numblk = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h7e = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h8s = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    chamol = new char[kmol][];
                    for (i0 = 0; i0 < kmol; i0++) {
                        chamol[i0] = new char[16];
                        for (i1 = 0; i1 < 16; i1++) {
                            numBytesRet += fis.Read(bytes, 0, sizeof(char));
                            chamol[i0][i1] = BitConverter.ToChar(bytes, 0);
                        }
                    }

                    nsize = sizeof(int);
                    idynam = new int[kmol];
                    for (i0 = 0; i0 < kmol; i0++) {
                        numBytesRet += fis.Read(bytes, 0, nsize);
                        idynam[i0] = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                    }

                idynam = new int[kmol];
                bytes = readBytes(fs, sizeof(int), kmol);
                for (i0 = 0; i0 < kmol; i++) {
                    idynam[i0] = BitConverter.ToInt32(bytes, i0 * sizeof(int));
                }
                Console.WriteLine(dt);

                    nsize = sizeof(int);
                    nummol0 = new int[kmol];
                    for (i0 = 0; i0 < kmol; i0++) {
                        numBytesRet += fis.Read(bytes, 0, nsize);
                        nummol0[i0] = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                    }
                    nsize = sizeof(int);
                    numatm = new int[kmol];
                    for (i0 = 0; i0 < kmol; i0++) {
                        numBytesRet += fis.Read(bytes, 0, nsize);
                        numatm[i0] = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                    }
                    nsize = sizeof(int);
                    numbon = new int[kmol];
                    for (i0 = 0; i0 < kmol; i0++) {
                        numBytesRet += fis.Read(bytes, 0, nsize);
                        numbon[i0] = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                    }
                    nsize = sizeof(int);
                    kindat = new int[kmol];
                    for (i0 = 0; i0 < kmol; i0++) {
                        numBytesRet += fis.Read(bytes, 0, nsize);
                        kindat[i0] = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                    }

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h8e = BitConverter.ToInt32(reverse(bytes, nsize), 0);

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h9s = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                    Console.WriteLine(h9s);

                    nsize = sizeof(int);
                    kinatm = new int[kmol][];
                    for (i0 = 0; i0 < kmol; i0++) {
                        kinatm[i0] = new int[numatm[i0]];
                        for (i1 = 0; i1 < numatm[i0]; i1++) {
                            numBytesRet += fis.Read(bytes, 0, nsize);
                            kinatm[i0][i1] = BitConverter.ToInt32(reverse(bytes, nsize), 0);
                        }
                    }
                    chatom = new char[kmol][][];
                    for (i0 = 0; i0 < kmol; i0++) {
                        chatom[i0] = new char[numatm[i0]][];
                        for (i1 = 0; i1 < numatm[i0]; i1++) {
                            chatom[i0][i1] = new char[2];
                            for (i2 = 0; i2 < 2; i2++) {
                                numBytesRet += fis.Read(bytes, 0, sizeof(char));
                                chatom[i0][i1][i2] = BitConverter.ToChar(bytes, 0);
                            }
                        }
                    }
                    atmkid = new char[kmol][][];
                    for (i0 = 0; i0 < kmol; i0++) {
                        atmkid[i0] = new char[numatm[i0]][];
                        for (i1 = 0; i1 < numatm[i0]; i1++) {
                            atmkid[i0][i1] = new char[2];
                            for (i2 = 0; i2 < 2; i2++) {
                                numBytesRet += fis.Read(bytes, 0, sizeof(char));
                                atmkid[i0][i1][i2] = BitConverter.ToChar(bytes, 0);
                            }
                        }
                    }
                    nsize = sizeof(float);
                    cmass = new float[kmol][];
                    for (i0 = 0; i0 < kmol; i0++) {
                        cmass[i0] = new float[numatm[i0]];
                        for (i1 = 0; i1 < numatm[i0]; i1++) {
                            numBytesRet += fis.Read(bytes, 0, nsize);
                            cmass[i0][i1] = BitConverter.ToSingle(reverse(bytes, nsize), 0);
                        }
                    }
                    nsize = sizeof(float);
                    charge = new float[kmol][];
                    for (i0 = 0; i0 < kmol; i0++) {
                        charge[i0] = new float[numatm[i0]];
                        for (i1 = 0; i1 < numatm[i0]; i1++) {
                            numBytesRet += fis.Read(bytes, 0, nsize);
                            charge[i0][i1] = BitConverter.ToSingle(reverse(bytes, nsize), 0);
                        }
                    }

                    nsize = sizeof(int);
                    numBytesRet += fis.Read(bytes, 0, nsize);
                    h9e = BitConverter.ToInt32(reverse(bytes, nsize), 0);

    /*
     *
     * To be implemented here
     *
     */
                    if (numBytesRet == 0) {
                        break;
                    }

                    numBytesRead += numBytesRet;
                    numBytesToRead -= numBytesRet;
                }
            }
        }
    }
}

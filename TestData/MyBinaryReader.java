import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MyBinaryReader {
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

		public MyBinaryReader() {}

		public void read(String filePath) throws IOException {
				int i, j, k, l;

				FileInputStream fis = new FileInputStream(filePath);
				DataInputStream dis = new DataInputStream(fis);
				ByteOrder bo = ByteOrder.BIG_ENDIAN;

				h1s = readBuf(dis, bo, 4).getInt();
				magic = readBuf(dis, bo, 4).getInt();
				h1e = readBuf(dis, bo, 4).getInt();
				h2s = readBuf(dis, bo, 4).getInt();
				fname = new byte[256];
				dis.read(fname);
				h2e = readBuf(dis, bo, 4).getInt();
				h3s = readBuf(dis, bo, 4).getInt();
				cdate = new byte[8];
				dis.read(cdate);
				mdate = new byte[8];
				dis.read(mdate);
				author = new byte[30];
				dis.read(author);
				h3e = readBuf(dis, bo, 4).getInt();
				h4s = readBuf(dis, bo, 4).getInt();
				commen = new byte[80];
				dis.read(commen);
				h4e = readBuf(dis, bo, 4).getInt();
				h5s = readBuf(dis, bo, 4).getInt();
				iresta = readBuf(dis, bo, 4).getInt();
				nstep = readBuf(dis, bo, 4).getInt();
				minit = readBuf(dis, bo, 4).getInt();
				mfinl = readBuf(dis, bo, 4).getInt();
				mintv = readBuf(dis, bo, 4).getInt();
				h5e = readBuf(dis, bo, 4).getInt();
				h6s = readBuf(dis, bo, 4).getInt();
				dt = readBuf(dis, bo, 4).getFloat();
				nsbloc = readBuf(dis, bo, 4).getInt();
				iensem = readBuf(dis, bo, 4).getInt();
				itemp = readBuf(dis, bo, 4).getInt();
				ipres = readBuf(dis, bo, 4).getInt();
				rcut = readBuf(dis, bo, 4).getFloat();
				h6e = readBuf(dis, bo, 4).getInt();
				h7s = readBuf(dis, bo, 4).getInt();
				natom0 = readBuf(dis, bo, 4).getInt();
				kmol = readBuf(dis, bo, 4).getInt();
				nummon = readBuf(dis, bo, 4).getInt();
				numthe = readBuf(dis, bo, 4).getInt();
				numrsv = readBuf(dis, bo, 4).getInt();
				numblk = readBuf(dis, bo, 4).getInt();
				h7e = readBuf(dis, bo, 4).getInt();
				h8s = readBuf(dis, bo, 4).getInt();
				chamol = new byte[kmol][];
				for (i = 0; i < kmol; i++) {
						chamol[i] = new byte[16];
						dis.read(chamol[i]);
				}
				idynam = new int[kmol];
				for (i = 0; i < kmol; i++) {
						idynam[i] = readBuf(dis, bo, 4).getInt();
				}
				nummol0 = new int[kmol];
				for (i = 0; i < kmol; i++) {
						nummol0[i] = readBuf(dis, bo, 4).getInt();
				}
				numatm = new int[kmol];
				for (i = 0; i < kmol; i++) {
						numatm[i] = readBuf(dis, bo, 4).getInt();
				}
				numbon = new int[kmol];
				for (i = 0; i < kmol; i++) {
						numbon[i] = readBuf(dis, bo, 4).getInt();
				}
				kindat = new int[kmol];
				for (i = 0; i < kmol; i++) {
						kindat[i] = readBuf(dis, bo, 4).getInt();
				}
				h8e = readBuf(dis, bo, 4).getInt();
				h9s = readBuf(dis, bo, 4).getInt();
				kinatm = new int[kmol][];
				for (i = 0; i < kmol; i++) {
						kinatm[i] = new int[numatm[i]];
						for (j = 0; j < numatm[i]; j++) {
								kinatm[i][j] = readBuf(dis, bo, 4).getInt();
						}
				}
				chatom = new byte[kmol][][];
				for (i = 0; i < kmol; i++) {
						chatom[i] = new byte[numatm[i]][];
						for (j = 0; j < numatm[i]; j++) {
								chatom[i][j] = new byte[2];
								dis.read(chatom[i][j]);
						}
				}
				atmkid = new byte[kmol][][];
				for (i = 0; i < kmol; i++) {
						atmkid[i] = new byte[numatm[i]][];
						for (j = 0; j < numatm[i]; j++) {
								atmkid[i][j] = new byte[2];
								dis.read(atmkid[i][j]);
						}
				}
				cmass = new float[kmol][];
				for (i = 0; i < kmol; i++) {
						cmass[i] = new float[numatm[i]];
						for (j = 0; j < numatm[i]; j++) {
								cmass[i][j] = readBuf(dis, bo, 4).getFloat();
						}
				}
				charge = new float[kmol][];
				for (i = 0; i < kmol; i++) {
						charge[i] = new float[numatm[i]];
						for (j = 0; j < numatm[i]; j++) {
								charge[i][j] = readBuf(dis, bo, 4).getFloat();
						}
				}
				h9e = readBuf(dis, bo, 4).getInt();

				dis.close();
				fis.close();

		}

		public static ByteBuffer readBuf(DataInputStream dis, ByteOrder bo, int size) throws IOException {
				byte[] buf = new byte[size];
				int nbytes = dis.read(buf);
				if (nbytes != size) {
						throw new IOException("Unexpected End of Stream");
				}
				return ByteBuffer.wrap(buf).order(bo);
		}

		public static void main(String[] args) {
				if (args.length != 1) {
						System.err.println("Usage: java MyBinaryReader filename");
						System.exit(-999);
				}
				try {
						MyBinaryReader br = new MyBinaryReader();
						br.read(args[0]);
{
    int i, j;
    for (i = 0; i < br.kmol; i++) {
        for (j = 0; j < br.numatm[i]; j++) {
            System.out.printf("charge[%d][%d] = %f\n", i, j, br.charge[i][j]);
        }
    }
}
				} catch (IOException e) {
						throw new RuntimeException(e.toString());
				}
		}
}

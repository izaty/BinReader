import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
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
        byte bytes[] = new byte[16];

        dis.read(bytes, 0, 4);
        h1s = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        magic = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h1e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h2s = ByteBuffer.wrap(bytes).order(bo).getInt();
        fname = new byte[256];
        dis.read(fname);
        dis.read(bytes, 0, 4);
        h2e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h3s = ByteBuffer.wrap(bytes).order(bo).getInt();
        cdate = new byte[8];
        dis.read(cdate);
        mdate = new byte[8];
        dis.read(mdate);
        author = new byte[30];
        dis.read(author);
        dis.read(bytes, 0, 4);
        h3e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h4s = ByteBuffer.wrap(bytes).order(bo).getInt();
        commen = new byte[80];
        dis.read(commen);
        dis.read(bytes, 0, 4);
        h4e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h5s = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        iresta = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        nstep = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        minit = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        mfinl = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        mintv = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h5e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h6s = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        dt = ByteBuffer.wrap(bytes).order(bo).getFloat();
        dis.read(bytes, 0, 4);
        nsbloc = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        iensem = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        itemp = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        ipres = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        rcut = ByteBuffer.wrap(bytes).order(bo).getFloat();
        dis.read(bytes, 0, 4);
        h6e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h7s = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        natom0 = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        kmol = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        nummon = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        numthe = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        numrsv = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        numblk = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h7e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h8s = ByteBuffer.wrap(bytes).order(bo).getInt();
        chamol = new byte[kmol][];
        for (i = 0; i < kmol; i++) {
            chamol[i] = new byte[16];
            dis.read(chamol[i]);
        }
        idynam = new int[kmol];
        for (i = 0; i < kmol; i++) {
            dis.read(bytes, 0, 4);
            idynam[i] = ByteBuffer.wrap(bytes).order(bo).getInt();
        }
        nummol0 = new int[kmol];
        for (i = 0; i < kmol; i++) {
            dis.read(bytes, 0, 4);
            nummol0[i] = ByteBuffer.wrap(bytes).order(bo).getInt();
        }
        numatm = new int[kmol];
        for (i = 0; i < kmol; i++) {
            dis.read(bytes, 0, 4);
            numatm[i] = ByteBuffer.wrap(bytes).order(bo).getInt();
        }
        numbon = new int[kmol];
        for (i = 0; i < kmol; i++) {
            dis.read(bytes, 0, 4);
            numbon[i] = ByteBuffer.wrap(bytes).order(bo).getInt();
        }
        kindat = new int[kmol];
        for (i = 0; i < kmol; i++) {
            dis.read(bytes, 0, 4);
            kindat[i] = ByteBuffer.wrap(bytes).order(bo).getInt();
        }
        dis.read(bytes, 0, 4);
        h8e = ByteBuffer.wrap(bytes).order(bo).getInt();
        dis.read(bytes, 0, 4);
        h9s = ByteBuffer.wrap(bytes).order(bo).getInt();
        kinatm = new int[kmol][];
        for (i = 0; i < kmol; i++) {
            kinatm[i] = new int[numatm[i]];
            for (j = 0; j < numatm[i]; j++) {
                dis.read(bytes, 0, 4);
                kinatm[i][j] = ByteBuffer.wrap(bytes).order(bo).getInt();
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
                dis.read(bytes, 0, 4);
                cmass[i][j] = ByteBuffer.wrap(bytes).order(bo).getFloat();
            }
        }
        charge = new float[kmol][];
        for (i = 0; i < kmol; i++) {
            charge[i] = new float[numatm[i]];
            for (j = 0; j < numatm[i]; j++) {
                dis.read(bytes, 0, 4);
                charge[i][j] = ByteBuffer.wrap(bytes).order(bo).getFloat();
            }
        }
        dis.read(bytes, 0, 4);
        h9e = ByteBuffer.wrap(bytes).order(bo).getInt();

        dis.close();
        fis.close();

    }

    public void write(String filePath) throws IOException {
        int i, j, k, l;

        FileOutputStream fos = new FileOutputStream(filePath);
        DataOutputStream dos = new DataOutputStream(fos);
        ByteOrder bo = ByteOrder.BIG_ENDIAN;
        byte bytes[] = new byte[16];

        ByteBuffer.wrap(bytes).order(bo).putInt(h1s);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(magic);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h1e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h2s);
        dos.write(bytes, 0, 4);
        dos.write(fname, 0, 256);
        ByteBuffer.wrap(bytes).order(bo).putInt(h2e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h3s);
        dos.write(bytes, 0, 4);
        dos.write(cdate, 0, 8);
        dos.write(mdate, 0, 8);
        dos.write(author, 0, 30);
        ByteBuffer.wrap(bytes).order(bo).putInt(h3e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h4s);
        dos.write(bytes, 0, 4);
        dos.write(commen, 0, 80);
        ByteBuffer.wrap(bytes).order(bo).putInt(h4e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h5s);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(iresta);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(nstep);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(minit);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(mfinl);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(mintv);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h5e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h6s);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putFloat(dt);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(nsbloc);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(iensem);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(itemp);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(ipres);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putFloat(rcut);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h6e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h7s);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(natom0);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(kmol);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(nummon);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(numthe);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(numrsv);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(numblk);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h7e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h8s);
        dos.write(bytes, 0, 4);
        for (i = 0; i < kmol; i++) {
            dos.write(chamol[i], 0, 16);
        }
        for (i = 0; i < kmol; i++) {
            ByteBuffer.wrap(bytes).order(bo).putInt(idynam[i]);
            dos.write(bytes, 0, 4);
        }
        for (i = 0; i < kmol; i++) {
            ByteBuffer.wrap(bytes).order(bo).putInt(nummol0[i]);
            dos.write(bytes, 0, 4);
        }
        for (i = 0; i < kmol; i++) {
            ByteBuffer.wrap(bytes).order(bo).putInt(numatm[i]);
            dos.write(bytes, 0, 4);
        }
        for (i = 0; i < kmol; i++) {
            ByteBuffer.wrap(bytes).order(bo).putInt(numbon[i]);
            dos.write(bytes, 0, 4);
        }
        for (i = 0; i < kmol; i++) {
            ByteBuffer.wrap(bytes).order(bo).putInt(kindat[i]);
            dos.write(bytes, 0, 4);
        }
        ByteBuffer.wrap(bytes).order(bo).putInt(h8e);
        dos.write(bytes, 0, 4);
        ByteBuffer.wrap(bytes).order(bo).putInt(h9s);
        dos.write(bytes, 0, 4);
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                ByteBuffer.wrap(bytes).order(bo).putInt(kinatm[i][j]);
                dos.write(bytes, 0, 4);
            }
        }
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                dos.write(chatom[i][j], 0, 2);
            }
        }
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                dos.write(atmkid[i][j], 0, 2);
            }
        }
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                ByteBuffer.wrap(bytes).order(bo).putFloat(cmass[i][j]);
                dos.write(bytes, 0, 4);
            }
        }
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                ByteBuffer.wrap(bytes).order(bo).putFloat(charge[i][j]);
                dos.write(bytes, 0, 4);
            }
        }
        ByteBuffer.wrap(bytes).order(bo).putInt(h9e);
        dos.write(bytes, 0, 4);

        dos.close();
        fos.close();

    }

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java MyBinaryReader inputfilename outputfilename");
            System.exit(-999);
        }
        try {
            MyBinaryReader br = new MyBinaryReader();
            br.read(args[0]);
    int i, j;
    for (i = 0; i < br.kmol; i++) {
        for (j = 0; j < br.numatm[i]; j++) {
            System.out.printf("charge[%d][%d] = %f\n", i, j, br.charge[i][j]);
        }
    }
            br.write(args[1]);
        } catch (IOException e) {
            throw new RuntimeException(e.toString());
        }
    }
}

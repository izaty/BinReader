#include <iostream>
#include <fstream>
#include <new>
using namespace std;

class MyBinaryReader
{
public:
    int h1s;
    int magic;
    int h1e;
    int h2s;
    char *fname;
    int h2e;
    int h3s;
    char *cdate;
    char *mdate;
    char *author;
    int h3e;
    int h4s;
    char *commen;
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
    char **chamol;
    int *idynam;
    int *nummol0;
    int *numatm;
    int *numbon;
    int *kindat;
    int h8e;
    int h9s;
    int **kinatm;
    char ***chatom;
    char ***atmkid;
    float **cmass;
    float **charge;
    int h9e;

protected:
    bool emptyContents;

public:
    MyBinaryReader() {emptyContents = true;}
    ~MyBinaryReader() {deleteContents();}

    int read(char *filePath);
    int write(char *filePath);
    void endianConvert(void *ptr, size_t size, size_t n);
    void deleteContents();
};

int MyBinaryReader::read(char *filePath)
{
    int i, j, k, l;

    try {
        ifstream fin;

        fin.open(filePath, ios::in | ios::binary);
        if (!fin) {
            return -3;
        }

        fin.read((char *)&h1s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h1s, sizeof(int), 1);
        fin.read((char *)&magic, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&magic, sizeof(int), 1);
        fin.read((char *)&h1e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h1e, sizeof(int), 1);
        fin.read((char *)&h2s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h2s, sizeof(int), 1);
        fname = new char[256];
        fin.read((char *)fname, 256 * sizeof(char));
        if (!fin) {
            return -1;
        }
        fin.read((char *)&h2e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h2e, sizeof(int), 1);
        fin.read((char *)&h3s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h3s, sizeof(int), 1);
        cdate = new char[8];
        fin.read((char *)cdate, 8 * sizeof(char));
        if (!fin) {
            return -1;
        }
        mdate = new char[8];
        fin.read((char *)mdate, 8 * sizeof(char));
        if (!fin) {
            return -1;
        }
        author = new char[30];
        fin.read((char *)author, 30 * sizeof(char));
        if (!fin) {
            return -1;
        }
        fin.read((char *)&h3e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h3e, sizeof(int), 1);
        fin.read((char *)&h4s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h4s, sizeof(int), 1);
        commen = new char[80];
        fin.read((char *)commen, 80 * sizeof(char));
        if (!fin) {
            return -1;
        }
        fin.read((char *)&h4e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h4e, sizeof(int), 1);
        fin.read((char *)&h5s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h5s, sizeof(int), 1);
        fin.read((char *)&iresta, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&iresta, sizeof(int), 1);
        fin.read((char *)&nstep, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&nstep, sizeof(int), 1);
        fin.read((char *)&minit, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&minit, sizeof(int), 1);
        fin.read((char *)&mfinl, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&mfinl, sizeof(int), 1);
        fin.read((char *)&mintv, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&mintv, sizeof(int), 1);
        fin.read((char *)&h5e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h5e, sizeof(int), 1);
        fin.read((char *)&h6s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h6s, sizeof(int), 1);
        fin.read((char *)&dt, sizeof(float));
        if (!fin) {
            return -1;
        }
        endianConvert(&dt, sizeof(float), 1);
        fin.read((char *)&nsbloc, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&nsbloc, sizeof(int), 1);
        fin.read((char *)&iensem, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&iensem, sizeof(int), 1);
        fin.read((char *)&itemp, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&itemp, sizeof(int), 1);
        fin.read((char *)&ipres, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&ipres, sizeof(int), 1);
        fin.read((char *)&rcut, sizeof(float));
        if (!fin) {
            return -1;
        }
        endianConvert(&rcut, sizeof(float), 1);
        fin.read((char *)&h6e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h6e, sizeof(int), 1);
        fin.read((char *)&h7s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h7s, sizeof(int), 1);
        fin.read((char *)&natom0, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&natom0, sizeof(int), 1);
        fin.read((char *)&kmol, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&kmol, sizeof(int), 1);
        fin.read((char *)&nummon, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&nummon, sizeof(int), 1);
        fin.read((char *)&numthe, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&numthe, sizeof(int), 1);
        fin.read((char *)&numrsv, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&numrsv, sizeof(int), 1);
        fin.read((char *)&numblk, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&numblk, sizeof(int), 1);
        fin.read((char *)&h7e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h7e, sizeof(int), 1);
        fin.read((char *)&h8s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h8s, sizeof(int), 1);
        chamol = new char*[kmol];
        for (i = 0; i < kmol; i++) {
            chamol[i] = new char[16];
            fin.read((char *)chamol[i], 16 * sizeof(char));
            if (!fin) {
                return -1;
            }
        }
        idynam = new int[kmol];
        fin.read((char *)idynam, kmol * sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(idynam, sizeof(int), kmol);
        nummol0 = new int[kmol];
        fin.read((char *)nummol0, kmol * sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(nummol0, sizeof(int), kmol);
        numatm = new int[kmol];
        fin.read((char *)numatm, kmol * sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(numatm, sizeof(int), kmol);
        numbon = new int[kmol];
        fin.read((char *)numbon, kmol * sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(numbon, sizeof(int), kmol);
        kindat = new int[kmol];
        fin.read((char *)kindat, kmol * sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(kindat, sizeof(int), kmol);
        fin.read((char *)&h8e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h8e, sizeof(int), 1);
        fin.read((char *)&h9s, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h9s, sizeof(int), 1);
        kinatm = new int*[kmol];
        for (i = 0; i < kmol; i++) {
            kinatm[i] = new int[numatm[i]];
            fin.read((char *)kinatm[i], numatm[i] * sizeof(int));
            if (!fin) {
                return -1;
            }
            endianConvert(kinatm[i], sizeof(int), numatm[i]);
        }
        chatom = new char**[kmol];
        for (i = 0; i < kmol; i++) {
            chatom[i] = new char*[numatm[i]];
            for (j = 0; j < numatm[i]; j++) {
                chatom[i][j] = new char[2];
                fin.read((char *)chatom[i][j], 2 * sizeof(char));
                if (!fin) {
                    return -1;
                }
            }
        }
        atmkid = new char**[kmol];
        for (i = 0; i < kmol; i++) {
            atmkid[i] = new char*[numatm[i]];
            for (j = 0; j < numatm[i]; j++) {
                atmkid[i][j] = new char[2];
                fin.read((char *)atmkid[i][j], 2 * sizeof(char));
                if (!fin) {
                    return -1;
                }
            }
        }
        cmass = new float*[kmol];
        for (i = 0; i < kmol; i++) {
            cmass[i] = new float[numatm[i]];
            fin.read((char *)cmass[i], numatm[i] * sizeof(float));
            if (!fin) {
                return -1;
            }
            endianConvert(cmass[i], sizeof(float), numatm[i]);
        }
        charge = new float*[kmol];
        for (i = 0; i < kmol; i++) {
            charge[i] = new float[numatm[i]];
            fin.read((char *)charge[i], numatm[i] * sizeof(float));
            if (!fin) {
                return -1;
            }
            endianConvert(charge[i], sizeof(float), numatm[i]);
        }
        fin.read((char *)&h9e, sizeof(int));
        if (!fin) {
            return -1;
        }
        endianConvert(&h9e, sizeof(int), 1);

        fin.close();
    }
    catch (bad_alloc) {
        return -2;
    }

    emptyContents = false;

    return 0;
}

void MyBinaryReader::endianConvert(void *ptr, size_t size, size_t n)
{
    if (size > 1) {
        int i, j;
        unsigned char ic[4];
        unsigned char *oc = (unsigned char *)ptr;

        for (i = 0; i < n; i++) {
            int base = i * size;
            for (j = 0; j < size; j++) {
                ic[size-j-1] = oc[base+j];
            }
            for (j = 0; j < size; j++) {
                oc[base+j] = ic[j];
            }
        }
    }
}

void MyBinaryReader::deleteContents()
{
    if (!emptyContents) {
    int i, j, k, l;

        for (i = 0; i < kmol; i++) {
            delete [] charge[i];
        }
        delete [] charge;
        for (i = 0; i < kmol; i++) {
            delete [] cmass[i];
        }
        delete [] cmass;
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                delete [] atmkid[i][j];
            }
            delete [] atmkid[i];
        }
        delete [] atmkid;
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                delete [] chatom[i][j];
            }
            delete [] chatom[i];
        }
        delete [] chatom;
        for (i = 0; i < kmol; i++) {
            delete [] kinatm[i];
        }
        delete [] kinatm;
        delete [] kindat;
        delete [] numbon;
        delete [] numatm;
        delete [] nummol0;
        delete [] idynam;
        for (i = 0; i < kmol; i++) {
            delete [] chamol[i];
        }
        delete [] chamol;
        delete [] commen;
        delete [] author;
        delete [] mdate;
        delete [] cdate;
        delete [] fname;

        emptyContents = true;
    }
}

int MyBinaryReader::write(char *filePath)
{
    int i, j, k, l;

    ofstream fout;

    fout.open(filePath, ios::out | ios::binary);
    if (!fout) {
        return -5;
    }

        endianConvert(&h1s, sizeof(int), 1);
        fout.write((char *)&h1s, sizeof(int));
        endianConvert(&h1s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&magic, sizeof(int), 1);
        fout.write((char *)&magic, sizeof(int));
        endianConvert(&magic, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h1e, sizeof(int), 1);
        fout.write((char *)&h1e, sizeof(int));
        endianConvert(&h1e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h2s, sizeof(int), 1);
        fout.write((char *)&h2s, sizeof(int));
        endianConvert(&h2s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        fout.write((char *)fname, 256 * sizeof(char));
        if (!fout) {
            return -4;
        }
        endianConvert(&h2e, sizeof(int), 1);
        fout.write((char *)&h2e, sizeof(int));
        endianConvert(&h2e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h3s, sizeof(int), 1);
        fout.write((char *)&h3s, sizeof(int));
        endianConvert(&h3s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        fout.write((char *)cdate, 8 * sizeof(char));
        if (!fout) {
            return -4;
        }
        fout.write((char *)mdate, 8 * sizeof(char));
        if (!fout) {
            return -4;
        }
        fout.write((char *)author, 30 * sizeof(char));
        if (!fout) {
            return -4;
        }
        endianConvert(&h3e, sizeof(int), 1);
        fout.write((char *)&h3e, sizeof(int));
        endianConvert(&h3e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h4s, sizeof(int), 1);
        fout.write((char *)&h4s, sizeof(int));
        endianConvert(&h4s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        fout.write((char *)commen, 80 * sizeof(char));
        if (!fout) {
            return -4;
        }
        endianConvert(&h4e, sizeof(int), 1);
        fout.write((char *)&h4e, sizeof(int));
        endianConvert(&h4e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h5s, sizeof(int), 1);
        fout.write((char *)&h5s, sizeof(int));
        endianConvert(&h5s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&iresta, sizeof(int), 1);
        fout.write((char *)&iresta, sizeof(int));
        endianConvert(&iresta, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&nstep, sizeof(int), 1);
        fout.write((char *)&nstep, sizeof(int));
        endianConvert(&nstep, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&minit, sizeof(int), 1);
        fout.write((char *)&minit, sizeof(int));
        endianConvert(&minit, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&mfinl, sizeof(int), 1);
        fout.write((char *)&mfinl, sizeof(int));
        endianConvert(&mfinl, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&mintv, sizeof(int), 1);
        fout.write((char *)&mintv, sizeof(int));
        endianConvert(&mintv, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h5e, sizeof(int), 1);
        fout.write((char *)&h5e, sizeof(int));
        endianConvert(&h5e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h6s, sizeof(int), 1);
        fout.write((char *)&h6s, sizeof(int));
        endianConvert(&h6s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&dt, sizeof(float), 1);
        fout.write((char *)&dt, sizeof(float));
        endianConvert(&dt, sizeof(float), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&nsbloc, sizeof(int), 1);
        fout.write((char *)&nsbloc, sizeof(int));
        endianConvert(&nsbloc, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&iensem, sizeof(int), 1);
        fout.write((char *)&iensem, sizeof(int));
        endianConvert(&iensem, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&itemp, sizeof(int), 1);
        fout.write((char *)&itemp, sizeof(int));
        endianConvert(&itemp, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&ipres, sizeof(int), 1);
        fout.write((char *)&ipres, sizeof(int));
        endianConvert(&ipres, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&rcut, sizeof(float), 1);
        fout.write((char *)&rcut, sizeof(float));
        endianConvert(&rcut, sizeof(float), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h6e, sizeof(int), 1);
        fout.write((char *)&h6e, sizeof(int));
        endianConvert(&h6e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h7s, sizeof(int), 1);
        fout.write((char *)&h7s, sizeof(int));
        endianConvert(&h7s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&natom0, sizeof(int), 1);
        fout.write((char *)&natom0, sizeof(int));
        endianConvert(&natom0, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&kmol, sizeof(int), 1);
        fout.write((char *)&kmol, sizeof(int));
        endianConvert(&kmol, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&nummon, sizeof(int), 1);
        fout.write((char *)&nummon, sizeof(int));
        endianConvert(&nummon, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&numthe, sizeof(int), 1);
        fout.write((char *)&numthe, sizeof(int));
        endianConvert(&numthe, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&numrsv, sizeof(int), 1);
        fout.write((char *)&numrsv, sizeof(int));
        endianConvert(&numrsv, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&numblk, sizeof(int), 1);
        fout.write((char *)&numblk, sizeof(int));
        endianConvert(&numblk, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h7e, sizeof(int), 1);
        fout.write((char *)&h7e, sizeof(int));
        endianConvert(&h7e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h8s, sizeof(int), 1);
        fout.write((char *)&h8s, sizeof(int));
        endianConvert(&h8s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        for (i = 0; i < kmol; i++) {
            fout.write((char *)chamol[i], 16 * sizeof(char));
            if (!fout) {
                return -4;
            }
        }
        endianConvert(idynam, sizeof(int), kmol);
        fout.write((char *)idynam, kmol * sizeof(int));
        endianConvert(idynam, sizeof(int), kmol);
        if (!fout) {
            return -4;
        }
        endianConvert(nummol0, sizeof(int), kmol);
        fout.write((char *)nummol0, kmol * sizeof(int));
        endianConvert(nummol0, sizeof(int), kmol);
        if (!fout) {
            return -4;
        }
        endianConvert(numatm, sizeof(int), kmol);
        fout.write((char *)numatm, kmol * sizeof(int));
        endianConvert(numatm, sizeof(int), kmol);
        if (!fout) {
            return -4;
        }
        endianConvert(numbon, sizeof(int), kmol);
        fout.write((char *)numbon, kmol * sizeof(int));
        endianConvert(numbon, sizeof(int), kmol);
        if (!fout) {
            return -4;
        }
        endianConvert(kindat, sizeof(int), kmol);
        fout.write((char *)kindat, kmol * sizeof(int));
        endianConvert(kindat, sizeof(int), kmol);
        if (!fout) {
            return -4;
        }
        endianConvert(&h8e, sizeof(int), 1);
        fout.write((char *)&h8e, sizeof(int));
        endianConvert(&h8e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        endianConvert(&h9s, sizeof(int), 1);
        fout.write((char *)&h9s, sizeof(int));
        endianConvert(&h9s, sizeof(int), 1);
        if (!fout) {
            return -4;
        }
        for (i = 0; i < kmol; i++) {
            endianConvert(kinatm[i], sizeof(int), numatm[i]);
            fout.write((char *)kinatm[i], numatm[i] * sizeof(int));
            endianConvert(kinatm[i], sizeof(int), numatm[i]);
            if (!fout) {
                return -4;
            }
        }
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                fout.write((char *)chatom[i][j], 2 * sizeof(char));
                if (!fout) {
                    return -4;
                }
            }
        }
        for (i = 0; i < kmol; i++) {
            for (j = 0; j < numatm[i]; j++) {
                fout.write((char *)atmkid[i][j], 2 * sizeof(char));
                if (!fout) {
                    return -4;
                }
            }
        }
        for (i = 0; i < kmol; i++) {
            endianConvert(cmass[i], sizeof(float), numatm[i]);
            fout.write((char *)cmass[i], numatm[i] * sizeof(float));
            endianConvert(cmass[i], sizeof(float), numatm[i]);
            if (!fout) {
                return -4;
            }
        }
        for (i = 0; i < kmol; i++) {
            endianConvert(charge[i], sizeof(float), numatm[i]);
            fout.write((char *)charge[i], numatm[i] * sizeof(float));
            endianConvert(charge[i], sizeof(float), numatm[i]);
            if (!fout) {
                return -4;
            }
        }
        endianConvert(&h9e, sizeof(int), 1);
        fout.write((char *)&h9e, sizeof(int));
        endianConvert(&h9e, sizeof(int), 1);
        if (!fout) {
            return -4;
        }

    fout.close();

    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " inputfilename outputfilename" << endl;
        return -999;
    }

    MyBinaryReader br;

    int err_code = br.read(argv[1]);
    if (err_code == -1) {
        cerr << "read error" << endl;
        return err_code;
    }
    if (err_code == -2) {
        cerr << "allocation error" << endl;
        return err_code;
    }
    if (err_code == -3) {
        cerr << "open error" << endl;
        return err_code;
    }
{
    volatile int i, j;
    for (i = 0; i < br.kmol; i++) {
        for (j = 0; j < br.numatm[i]; j++) {
            cerr << "charge[" << i << "][" << j << "] = " << br.charge[i][j] << endl;
        }
    }
}
    err_code = br.write(argv[2]);
    if (err_code == -4) {
        cerr << "write error" << endl;
        return err_code;
    }
    if (err_code == -5) {
        cerr << "open error" << endl;
        return err_code;
    }

    return 0;
}

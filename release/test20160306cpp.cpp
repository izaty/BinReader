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
	void endianConvert(void *ptr, size_t size, size_t n);
	void deleteContents();
};

int MyBinaryReader::read(char *filePath)
{
	volatile int i0, i1, i2, i3;

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
		for (i0 = 0; i0 < kmol; i0++) {
			chamol[i0] = new char[16];
			fin.read((char *)chamol[i0], 16 * sizeof(char));
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
		for (i0 = 0; i0 < kmol; i0++) {
			kinatm[i0] = new int[numatm[i0]];
			fin.read((char *)kinatm[i0], numatm[i0] * sizeof(int));
			if (!fin) {
				return -1;
			}
			endianConvert(kinatm[i0], sizeof(int), numatm[i0]);
		}
		chatom = new char**[kmol];
		for (i0 = 0; i0 < kmol; i0++) {
			chatom[i0] = new char*[numatm[i0]];
			for (i1 = 0; i1 < numatm[i0]; i1++) {
				chatom[i0][i1] = new char[2];
				fin.read((char *)chatom[i0][i1], 2 * sizeof(char));
				if (!fin) {
					return -1;
				}
			}
		}
		atmkid = new char**[kmol];
		for (i0 = 0; i0 < kmol; i0++) {
			atmkid[i0] = new char*[numatm[i0]];
			for (i1 = 0; i1 < numatm[i0]; i1++) {
				atmkid[i0][i1] = new char[2];
				fin.read((char *)atmkid[i0][i1], 2 * sizeof(char));
				if (!fin) {
					return -1;
				}
			}
		}
		cmass = new float*[kmol];
		for (i0 = 0; i0 < kmol; i0++) {
			cmass[i0] = new float[numatm[i0]];
			fin.read((char *)cmass[i0], numatm[i0] * sizeof(float));
			if (!fin) {
				return -1;
			}
			endianConvert(cmass[i0], sizeof(float), numatm[i0]);
		}
		charge = new float*[kmol];
		for (i0 = 0; i0 < kmol; i0++) {
			charge[i0] = new float[numatm[i0]];
			fin.read((char *)charge[i0], numatm[i0] * sizeof(float));
			if (!fin) {
				return -1;
			}
			endianConvert(charge[i0], sizeof(float), numatm[i0]);
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
		unsigned char ic[64];
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
	volatile int i0, i1, i2, i3;

		for (i0 = 0; i0 < kmol; i0++) {
			delete [] charge[i0];
		}
		delete [] charge;
		for (i0 = 0; i0 < kmol; i0++) {
			delete [] cmass[i0];
		}
		delete [] cmass;
		for (i0 = 0; i0 < kmol; i0++) {
			for (i1 = 0; i1 < numatm[i0]; i1++) {
				delete [] atmkid[i0][i1];
			}
			delete [] atmkid[i0];
		}
		delete [] atmkid;
		for (i0 = 0; i0 < kmol; i0++) {
			for (i1 = 0; i1 < numatm[i0]; i1++) {
				delete [] chatom[i0][i1];
			}
			delete [] chatom[i0];
		}
		delete [] chatom;
		for (i0 = 0; i0 < kmol; i0++) {
			delete [] kinatm[i0];
		}
		delete [] kinatm;
		delete [] kindat;
		delete [] numbon;
		delete [] numatm;
		delete [] nummol0;
		delete [] idynam;
		for (i0 = 0; i0 < kmol; i0++) {
			delete [] chamol[i0];
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

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		return -999;
	}

	MyBinaryReader br;

	int err_code = br.read(argv[1]);
	if (err_code == -1) {
		fprintf(stderr, "read error\n");
		return err_code;
	}
	if (err_code == -2) {
		fprintf(stderr, "allocation error\n");
		return err_code;
	}
	if (err_code == -3) {
		fprintf(stderr, "open error\n");
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

	return 0;
}

#include <stdio.h>
#include <stdlib.h>

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

void econv(void *ptr, size_t size, size_t n)
{
    int i, j;
    unsigned char *ptr_uc = (unsigned char *)ptr;
    unsigned char work[4];

    for (i = 0; i < n; i++) {
        int base = i * size;
        for (j = 0; j < size; j++) {
            work[size-j-1] = ptr_uc[base+j];
        }
        for (j = 0; j < size; j++) {
            ptr_uc[base+j] = work[j];
        }
    }
}

size_t eread(void *ptr, size_t size, size_t n, FILE *stream)
{
    size_t ret_code;
    if (size > 1) {
        ret_code = fread(ptr, size, n, stream);
        econv(ptr, size, n);
    }
    else {
        ret_code = fread(ptr, size, n, stream);
    }

    return ret_code;
}

size_t ewrite(void *ptr, size_t size, size_t n, FILE *stream)
{
    size_t ret_code;
    if (size > 1) {
        econv(ptr, size, n);
        ret_code = fwrite(ptr, size, n, stream);
        econv(ptr, size, n);
    }
    else {
        ret_code = fwrite(ptr, size, n, stream);
    }

    return ret_code;
}

int readBinary(char *filePath)
{
    int i, j, k, l;

    FILE *fp;

    if ((fp = fopen(filePath, "rb")) == NULL) {
        return -3;
    }

    if (eread(&h1s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&magic, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h1e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h2s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if ((fname = (char *)malloc(256 * sizeof(char))) == NULL) {
        return -2;
    }
    if (eread(fname, sizeof(char), 256, fp) != 256) {
        return -1;
    }
    if (eread(&h2e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h3s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if ((cdate = (char *)malloc(8 * sizeof(char))) == NULL) {
        return -2;
    }
    if (eread(cdate, sizeof(char), 8, fp) != 8) {
        return -1;
    }
    if ((mdate = (char *)malloc(8 * sizeof(char))) == NULL) {
        return -2;
    }
    if (eread(mdate, sizeof(char), 8, fp) != 8) {
        return -1;
    }
    if ((author = (char *)malloc(30 * sizeof(char))) == NULL) {
        return -2;
    }
    if (eread(author, sizeof(char), 30, fp) != 30) {
        return -1;
    }
    if (eread(&h3e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h4s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if ((commen = (char *)malloc(80 * sizeof(char))) == NULL) {
        return -2;
    }
    if (eread(commen, sizeof(char), 80, fp) != 80) {
        return -1;
    }
    if (eread(&h4e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h5s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&iresta, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&nstep, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&minit, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&mfinl, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&mintv, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h5e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h6s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&dt, sizeof(float), 1, fp) != 1) {
        return -1;
    }
    if (eread(&nsbloc, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&iensem, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&itemp, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&ipres, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&rcut, sizeof(float), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h6e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h7s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&natom0, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&kmol, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&nummon, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&numthe, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&numrsv, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&numblk, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h7e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h8s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if ((chamol = (char **)malloc(kmol * sizeof(char *))) == NULL) {
        return -2;
    }
    for (i = 0; i < kmol; i++) {
        if ((chamol[i] = (char *)malloc(16 * sizeof(char))) == NULL) {
            return -2;
        }
        if (eread(chamol[i], sizeof(char), 16, fp) != 16) {
            return -1;
        }
    }
    if ((idynam = (int *)malloc(kmol * sizeof(int))) == NULL) {
        return -2;
    }
    if (eread(idynam, sizeof(int), kmol, fp) != kmol) {
        return -1;
    }
    if ((nummol0 = (int *)malloc(kmol * sizeof(int))) == NULL) {
        return -2;
    }
    if (eread(nummol0, sizeof(int), kmol, fp) != kmol) {
        return -1;
    }
    if ((numatm = (int *)malloc(kmol * sizeof(int))) == NULL) {
        return -2;
    }
    if (eread(numatm, sizeof(int), kmol, fp) != kmol) {
        return -1;
    }
    if ((numbon = (int *)malloc(kmol * sizeof(int))) == NULL) {
        return -2;
    }
    if (eread(numbon, sizeof(int), kmol, fp) != kmol) {
        return -1;
    }
    if ((kindat = (int *)malloc(kmol * sizeof(int))) == NULL) {
        return -2;
    }
    if (eread(kindat, sizeof(int), kmol, fp) != kmol) {
        return -1;
    }
    if (eread(&h8e, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if (eread(&h9s, sizeof(int), 1, fp) != 1) {
        return -1;
    }
    if ((kinatm = (int **)malloc(kmol * sizeof(int *))) == NULL) {
        return -2;
    }
    for (i = 0; i < kmol; i++) {
        if ((kinatm[i] = (int *)malloc(numatm[i] * sizeof(int))) == NULL) {
            return -2;
        }
        if (eread(kinatm[i], sizeof(int), numatm[i], fp) != numatm[i]) {
            return -1;
        }
    }
    if ((chatom = (char ***)malloc(kmol * sizeof(char **))) == NULL) {
        return -2;
    }
    for (i = 0; i < kmol; i++) {
        if ((chatom[i] = (char **)malloc(numatm[i] * sizeof(char *))) == NULL) {
            return -2;
        }
        for (j = 0; j < numatm[i]; j++) {
            if ((chatom[i][j] = (char *)malloc(2 * sizeof(char))) == NULL) {
                return -2;
            }
            if (eread(chatom[i][j], sizeof(char), 2, fp) != 2) {
                return -1;
            }
        }
    }
    if ((atmkid = (char ***)malloc(kmol * sizeof(char **))) == NULL) {
        return -2;
    }
    for (i = 0; i < kmol; i++) {
        if ((atmkid[i] = (char **)malloc(numatm[i] * sizeof(char *))) == NULL) {
            return -2;
        }
        for (j = 0; j < numatm[i]; j++) {
            if ((atmkid[i][j] = (char *)malloc(2 * sizeof(char))) == NULL) {
                return -2;
            }
            if (eread(atmkid[i][j], sizeof(char), 2, fp) != 2) {
                return -1;
            }
        }
    }
    if ((cmass = (float **)malloc(kmol * sizeof(float *))) == NULL) {
        return -2;
    }
    for (i = 0; i < kmol; i++) {
        if ((cmass[i] = (float *)malloc(numatm[i] * sizeof(float))) == NULL) {
            return -2;
        }
        if (eread(cmass[i], sizeof(float), numatm[i], fp) != numatm[i]) {
            return -1;
        }
    }
    if ((charge = (float **)malloc(kmol * sizeof(float *))) == NULL) {
        return -2;
    }
    for (i = 0; i < kmol; i++) {
        if ((charge[i] = (float *)malloc(numatm[i] * sizeof(float))) == NULL) {
            return -2;
        }
        if (eread(charge[i], sizeof(float), numatm[i], fp) != numatm[i]) {
            return -1;
        }
    }
    if (eread(&h9e, sizeof(int), 1, fp) != 1) {
        return -1;
    }

    fclose(fp);

    return 0;
}

void deleteContents()
{
    int i, j, k, l;

    for (i = 0; i < kmol; i++) {
        free(charge[i]);
    }
    free(charge);
    for (i = 0; i < kmol; i++) {
        free(cmass[i]);
    }
    free(cmass);
    for (i = 0; i < kmol; i++) {
        for (j = 0; j < numatm[i]; j++) {
            free(atmkid[i][j]);
        }
        free(atmkid[i]);
    }
    free(atmkid);
    for (i = 0; i < kmol; i++) {
        for (j = 0; j < numatm[i]; j++) {
            free(chatom[i][j]);
        }
        free(chatom[i]);
    }
    free(chatom);
    for (i = 0; i < kmol; i++) {
        free(kinatm[i]);
    }
    free(kinatm);
    free(kindat);
    free(numbon);
    free(numatm);
    free(nummol0);
    free(idynam);
    for (i = 0; i < kmol; i++) {
        free(chamol[i]);
    }
    free(chamol);
    free(commen);
    free(author);
    free(mdate);
    free(cdate);
    free(fname);
}

int writeBinary(char *filePath)
{
    int i, j, k, l;

    FILE *fp;

    if ((fp = fopen(filePath, "wb")) == NULL) {
        return -5;
    }

    if (ewrite(&h1s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&magic, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h1e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h2s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(fname, sizeof(char), 256, fp) != 256) {
        return -4;
    }
    if (ewrite(&h2e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h3s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(cdate, sizeof(char), 8, fp) != 8) {
        return -4;
    }
    if (ewrite(mdate, sizeof(char), 8, fp) != 8) {
        return -4;
    }
    if (ewrite(author, sizeof(char), 30, fp) != 30) {
        return -4;
    }
    if (ewrite(&h3e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h4s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(commen, sizeof(char), 80, fp) != 80) {
        return -4;
    }
    if (ewrite(&h4e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h5s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&iresta, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&nstep, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&minit, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&mfinl, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&mintv, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h5e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h6s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&dt, sizeof(float), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&nsbloc, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&iensem, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&itemp, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&ipres, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&rcut, sizeof(float), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h6e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h7s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&natom0, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&kmol, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&nummon, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&numthe, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&numrsv, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&numblk, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h7e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h8s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    for (i = 0; i < kmol; i++) {
        if (ewrite(chamol[i], sizeof(char), 16, fp) != 16) {
            return -4;
        }
    }
    if (ewrite(idynam, sizeof(int), kmol, fp) != kmol) {
        return -4;
    }
    if (ewrite(nummol0, sizeof(int), kmol, fp) != kmol) {
        return -4;
    }
    if (ewrite(numatm, sizeof(int), kmol, fp) != kmol) {
        return -4;
    }
    if (ewrite(numbon, sizeof(int), kmol, fp) != kmol) {
        return -4;
    }
    if (ewrite(kindat, sizeof(int), kmol, fp) != kmol) {
        return -4;
    }
    if (ewrite(&h8e, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    if (ewrite(&h9s, sizeof(int), 1, fp) != 1) {
        return -4;
    }
    for (i = 0; i < kmol; i++) {
        if (ewrite(kinatm[i], sizeof(int), numatm[i], fp) != numatm[i]) {
            return -4;
        }
    }
    for (i = 0; i < kmol; i++) {
        for (j = 0; j < numatm[i]; j++) {
            if (ewrite(chatom[i][j], sizeof(char), 2, fp) != 2) {
                return -4;
            }
        }
    }
    for (i = 0; i < kmol; i++) {
        for (j = 0; j < numatm[i]; j++) {
            if (ewrite(atmkid[i][j], sizeof(char), 2, fp) != 2) {
                return -4;
            }
        }
    }
    for (i = 0; i < kmol; i++) {
        if (ewrite(cmass[i], sizeof(float), numatm[i], fp) != numatm[i]) {
            return -4;
        }
    }
    for (i = 0; i < kmol; i++) {
        if (ewrite(charge[i], sizeof(float), numatm[i], fp) != numatm[i]) {
            return -4;
        }
    }
    if (ewrite(&h9e, sizeof(int), 1, fp) != 1) {
        return -4;
    }

    fclose(fp);

    return 0;
}

int main(int argc, char **argv)
{
    int err_code;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s inputfilename outputfilename\n", argv[0]);
        return -999;
    }

    err_code = readBinary(argv[1]);

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
            int i, j;
            for (i = 0; i < kmol; i++) {
                for (j = 0; j < numatm[i]; j++) {
                     fprintf(stderr, "charge[%d][%d] = %f\n", i, j, charge[i][j]);
                }
            }
        }

    err_code = writeBinary(argv[2]);

    if (err_code == -4) {
        fprintf(stderr, "write error\n");
        return err_code;
    }
    if (err_code == -5) {
        fprintf(stderr, "open error\n");
        return err_code;
    }

    deleteContents();

    return 0;
}

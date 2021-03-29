import java.util.Random;

class PeakFinder2D {
    int[][] a;
    int nrow, ncol;

    public PeakFinder2D(int row, int col) {
        nrow = row;
        ncol = col;
        a = new int[nrow][ncol];
        Random r = new Random();
        for (int i = 0; i < nrow; i++) {
            for (int j = 0; j < ncol; j++) {
                a[i][j] = r.nextInt(10);
            }
        }
    }

    public int greedyAlg() {  //0,0 noktasından başlayarak 4 kenarı (çaprazlar yok) kontrol ederek hep en büyüğü takip ederek peak noktasını bulan algoritme.
        int row = 0;
        int col = 0;
        int peak, x, y, z, t;
        int maxOlanIndex = 0;
        while (true) {
            peak = a[row][col];  //eğer çevresindeki 4 sayı varsa o değerleri al yoksa olmayan(kenarlar) değerler yerine "0" al fazla kontrol ve  if else yapısından kurtul.
            x = ((col + 1 < ncol - 1) ? a[row][col + 1] : 0);
            y = ((col - 1) > 0 ? a[row][col - 1] : 0);
            z = ((row + 1 < nrow - 1) ? a[row + 1][col] : 0);
            t = ((row - 1) > 0 ? a[row - 1][col] : 0);
            int[] b = {peak, x, y, z, t};
            System.out.println("çevre sayılar;");
            System.out.println(peak);
            System.out.println(x);
            System.out.println(y);
            System.out.println(z);
            System.out.println(t);
            int max = b[0];
            for (int i = 0; i < b.length; i++) {
                if (b[i] > max) {
                    max = b[i];
                    maxOlanIndex = i;
                }
            }
            System.out.println("max:" + max);
            if (peak == max) {
                return peak;
            } else {
                switch (maxOlanIndex) {  //döngüden elde edilen max değer hangi indeksteyse o index değerleini taımlanan ilk peak'e atayıp döngünün devamlılğını sağla hep büyük yönünde ilerlesin.
                    case 0:
                        return peak;
                    case 1:   //dizi de 1.index a[row][col + 1]
                        row = row;
                        col = col + 1;
                        break;
                    case 2:   //dizi de 2.index a[row][col - 1]
                        row = row;
                        col = col - 1;
                        break;
                    case 3:   //dizi de 3.index a[row + 1][col]
                        row = row + 1;
                        col = col;
                        break;
                    case 4:   //dizi de 4.index a[row - 1][col]
                        row = row - 1;
                        col = col;
                        break;
                }
            }
        }
    }

    public int findMax(int[] b) {
        int imax = 0;
        for (int i = 0; i < a.length; i++) {
            if (b[i] > b[imax]) {
                imax = i;
            }
        }
        return imax;
    }

    public int findMaxOnCol1(int col) { //divideAndConquer1 için max col bulan fonk.
        int imax = 0;
        for (int i = 0; i < nrow; i++) {
            if (a[i][col] > a[imax][col]) {
                imax = i;
            }
        }
        return imax;
    }

    public int findMaxOnCol2(int col, int mrow) {
        int imax = mrow;   //dizi bölündükten sonra max seçilen kısma bakılsın tüm diziye değil.
        for (int i = mrow; i < nrow; i++) {
            if (a[i][col] > a[imax][col]) {
                imax = i;
            }
        }
        return imax;
    }

    public int findMaxOnRow(int row, int mcol) {
        int imax = mcol;  //dizi bölündükten sonra max seçilen kısma bakılsın tüm diziye değil.
        for (int i = mcol; i < ncol; i++) {
            if (a[row][i] > a[row][imax]) {
                imax = i;
            }
        }
        return imax;
    }

    public int divideAndConquer1(int startcol, int endcol) {
        //TODO correct and complete the code
        int midcol = (int) (endcol + startcol) / 2; //1 tane
        System.out.println("midcol:" + midcol);
        int imax = findMaxOnCol1(midcol); // number of rows: m
        System.out.println("imax:" + imax);
        ///base case TODO: boundary conditions
        if (midcol == 0 || midcol == ncol - 1)
            return a[imax][midcol];
        if (midcol == startcol || midcol == endcol)
            return a[imax][midcol];
        if (a[imax][midcol] >= a[imax][midcol + 1] && a[imax][midcol] >= a[imax][midcol - 1]) //2 tane
            return a[imax][midcol];
        else if (a[imax][midcol] <= a[imax][midcol + 1] && a[imax][midcol + 1] > a[imax][midcol - 1])
            return divideAndConquer1(midcol, endcol);
        else if (a[imax][midcol] <= a[imax][midcol - 1] && a[imax][midcol - 1] > a[imax][midcol + 1])
            return divideAndConquer1(startcol, midcol);

        //System.out.println("peak noktası:"+a[imax][midcol]);
        return a[imax][midcol];
    }

    /**
     * derste anlatilan divide and conquer  yontemini kullanarak O(n+m)
     * zamanda peak bulan algoritmanin implemantasyonunu yaziniz
     */
    public int divideAndConquer2(int startrow, int startcol, int endrow, int endcol) {
        //TODO
        ncol = endcol;   //dizimin yeni boyutu sürekli küçüleceği için boyutlarınıda değiştiriyoruz.
        nrow = endrow;
        if (endcol - startcol >= endrow - startrow) {   //row büyükse önce rowu böler col büyükse önce colu bölen en dıştaki if - else yapısı
            int midcol = (int) (endcol + startcol) / 2;
            System.out.println("midcol:" + midcol);
            int imax = findMaxOnCol2(midcol, startrow);

            System.out.println("imax:" + imax);
            if (midcol == 0 || midcol == ncol - 1) {
                return a[imax][midcol];
            }
            if (midcol == startcol || midcol == endcol) {
                return a[imax][midcol];
            }
            if (a[imax][midcol] >= a[imax][midcol + 1] && a[imax][midcol] >= a[imax][midcol - 1]) {//2 tane
                return a[imax][midcol];
            } else if (a[imax][midcol] <= a[imax][midcol + 1] && a[imax][midcol + 1] > a[imax][midcol - 1]) {
                return divideAndConquer2(startrow, midcol + 1, endrow, endcol);
            } else if (a[imax][midcol] <= a[imax][midcol - 1] && a[imax][midcol - 1] > a[imax][midcol + 1]) {
                return divideAndConquer2(startrow, startcol, endrow, midcol + 1);
            }
            return a[imax][midcol];
        } else {
            int midrow = (int) (endrow + startrow) / 2;
            System.out.println("midrow:" + midrow);
            int jmax = findMaxOnRow(midrow, startcol);

            System.out.println("jmax:" + jmax);
            if (midrow == 0 || midrow == nrow - 1) {
                return a[midrow][jmax];
            }
            if (midrow == startrow || midrow == endrow) {
                return a[midrow][jmax];
            }
            if (a[midrow][jmax] >= a[midrow + 1][jmax] && a[midrow][jmax] >= a[midrow - 1][jmax]) {
                return a[midrow][jmax];
            } else if (a[midrow][jmax] <= a[midrow + 1][jmax] && a[midrow + 1][jmax] > a[midrow - 1][jmax]) {
                return divideAndConquer2(midrow, startcol, endrow, endcol);
            } else if (a[midrow][jmax] <= a[midrow - 1][jmax] && a[midrow - 1][jmax] > a[midrow + 1][jmax]) {
                return divideAndConquer2(startrow, startcol, midrow, endcol);
            }
            return a[midrow][jmax];
        }
    }

    /**
     * prints elements of a
     */
    void printArray() {
        //TODO
        for (int i = 0; i < a.length; ++i) {
            for (int j = 0; j < a[i].length; ++j) {
                System.out.print(a[i][j] + "\t");
            }
            System.out.println("");
        }
    }

    static void testGreedyAlg() {
        //TODO
        PeakFinder2D O = new PeakFinder2D(5, 7);
        O.printArray();
        System.out.println("Greedy Algoritması ile Peak Noktası:" + O.greedyAlg());
    }

    static void testDivideAndConq1() {
        //TODO
        PeakFinder2D O = new PeakFinder2D(5, 7);
        O.printArray();
        System.out.println("Divide and Conquer Algoritması ile Peak Noktası:" + O.divideAndConquer1(0, O.ncol));

    }

    static void testDivideAndConq2() {
        //TODO
        PeakFinder2D O = new PeakFinder2D(5, 7);
        O.printArray();
        System.out.println("Divide and Conquer Algoritması2 ile Peak Noktası:" + O.divideAndConquer2(0, 0, O.nrow, O.ncol));
    }
}

public class Main {

    public static void main(String[] args) {
        // write your code here
        PeakFinder2D.testGreedyAlg();
        PeakFinder2D.testDivideAndConq1();
        PeakFinder2D.testDivideAndConq2();
    }
}

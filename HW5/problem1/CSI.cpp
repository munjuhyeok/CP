#include "CSI.h"

Complex::Complex(): real(0), imag(0) {}

CSI::CSI(): data(nullptr), num_packets(0), num_channel(0), num_subcarrier(0) {}

CSI::~CSI() {
    if(data) {
        for(int i = 0 ; i < num_packets; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
}

int CSI::packet_length() const {
    return num_channel * num_subcarrier;
}

void CSI::print(std::ostream& os) const {
    for (int i = 0; i < num_packets; i++) {
        for (int j = 0; j < packet_length(); j++) {
            os << data[i][j] << ' ';
        }
        os << std::endl;
    }
}

std::ostream& operator<<(std::ostream &os, const Complex &c) {
    // TODO: problem 1.1
    return os<<c.real<<"+"<<c.imag<<"i";
}

void read_csi(const char* filename, CSI* csi) {
    // TODO: problem 1.2
    std::string str;
    std::ifstream ifs(filename);

    std::getline(ifs, str);
    int np = std::stoi(str);
    csi->num_packets = np;
    std::getline(ifs, str);
    int nc = std::stoi(str);
    csi->num_channel = nc;
    std::getline(ifs, str);
    int nsc = std::stoi(str);
    csi->num_subcarrier = nsc;

    csi->data = new Complex*[np];
    for (int i = 0; i<np; i++){
        csi->data[i] = new Complex[nc*nsc];
        for(int j = 0; j<nsc; j++){
            for(int k = 0; k<nc; k++){
                std::getline(ifs,str);
                int real = std::stoi(str);
                std::getline(ifs,str);
                int imag = std::stoi(str);
                csi->data[i][j+nsc*k].real = real ;
                csi->data[i][j+nsc*k].imag = imag ;
            }
        }
    }
    ifs.close();
}

float** decode_csi(CSI* csi) {
    // TODO: problem 1.3
    float** amp;
    int np = csi->num_packets;
    int nc = csi->num_channel;
    int nsc = csi->num_subcarrier;
    amp = new float *[np];
    for (int i = 0; i<np; i++) {
        amp[i] = new float [nc * nsc];
        for(int j = 0; j<nsc; j++) {
            for (int k = 0; k < nc; k++) {
                int real = csi->data[i][j+nsc*k].real;
                int imag = csi->data[i][j+nsc*k].imag;
                amp[i][j + nsc * k] = sqrt(real * real + imag * imag);
            }
        }
    }
    return amp;
}

float* get_std(float** decoded_csi, int num_packets, int packet_length) {
    // TODO: problem 1.4
    float* std;
    std = new float[num_packets];
    for (int i = 0; i<num_packets; i++){
        std[i] = standard_deviation(decoded_csi[i],packet_length);
    }

    return std;
}

void save_std(float* std_arr, int num_packets, const char* filename) {
    // TODO: problem 1.5
    std::ofstream ofs(filename);
    for (int i = 0; i<num_packets;i++) {
        ofs << std_arr[i]<<" ";
    }
    ofs.close();
}

// convenience functions
float standard_deviation(float* data, int array_length) {
    float mean = 0, var = 0;
    for (int i = 0; i < array_length; i++) {
        mean += data[i];
    }
    mean /= array_length;
    for (int i = 0; i < array_length; i++) {
        var += pow(data[i]-mean,2);
    }
    var /= array_length;
    return sqrt(var);
}
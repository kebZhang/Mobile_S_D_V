rm diag_revealer
rm diag_revealer.c
rm decode.c
rm decode.h
rm generate_diag_cfg.h
rm generate_diag_cfg.c
rm Android.mk
rm -r asn1_group

cp /vagrant/Ty_apk/S_D_V_diagrevealer/diag_revealer.c ./
cp /vagrant/Ty_apk/S_D_V_diagrevealer/decode.c ./
cp /vagrant/Ty_apk/S_D_V_diagrevealer/decode.h ./
cp /vagrant/Ty_apk/S_D_V_diagrevealer/generate_diag_cfg.h ./
cp /vagrant/Ty_apk/S_D_V_diagrevealer/generate_diag_cfg.c ./
cp /vagrant/Ty_apk/S_D_V_diagrevealer/Android.mk ./
cp -r /vagrant/Ty_apk/S_D_V_diagrevealer/asn1_group ./

sudo make ndk-build='/home/vagrant/android-ndk-r19b/ndk-build'
cp diag_revealer /vagrant/Ty_apk/S_D_V_diagrevealer/
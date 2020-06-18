#include "teacherop.h"
#include <vector>
#include <QString>
using namespace std;

Teacherop::Teacherop(Teacherclient* teacherclient) {
    this->teacherclient = teacherclient;
}

Teacherop::~Teacherop() {;}
    
void Teacherop::send_audiopiece(string& audio) {
    this->teacherclient->send_audiopiece(audio);
}

string Teacherop::receive_msg() {
    return this->teacherclient->receive_msg();
}

void Teacherop::randcall() {
    this->teacherclient->randcall();
}

void Teacherop::endcall() {
    this->teacherclient->endcall();
}

void Teacherop::send_prob(string prob, string ans, string right_ans) {
    this->teacherclient->send_prob(prob, ans, right_ans);
}

void Teacherop::pull_prob()
{
    teacherclient->pull_prob();
}

void Teacherop::get_window_title_list(vector<pair<QString, HWND> >& list)
{
    vector<pair<string, HWND> > stdlist;
    teacherclient->get_window_title_list(stdlist);
    for (int i = 0; i < stdlist.size(); i++) {
        list.push_back(make_pair(QString::fromStdString(stdlist[i].first), stdlist[i].second));
    }
}

void Teacherop::send_vid(QByteArray& data)
{
    string msg = data.toStdString();
    teacherclient->send_vid(msg);
}

void Teacherop::add_record(const string& username, const string& start_time,
                           const string& quit_time, const string& att_ratio)
{
    teacherclient->add_record(username, start_time, quit_time, att_ratio);
}

void Teacherop::get_records(vector<Record*>& records)
{
    for (int i = 0; i < teacherclient->records.size(); i++) {
        Record* rec = teacherclient->records[i];
        records.push_back(rec);
    }
    printf("get_records: records size: %d\n", records.size());
}

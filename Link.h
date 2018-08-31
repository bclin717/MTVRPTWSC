//
// Created by kevin on 2018/8/29.
//

#ifndef MTVRPTWSC_LINK_H
#define MTVRPTWSC_LINK_H

class Link {
public:
    Link();
    Link(int s, int e, float saving);
    void setStart(int s);
    int getStart();

    void setEnd(int e);
    int getEnd();

    void setSaving(float s);
    float getSaving();

    static bool cmp(const Link &l1, const Link &l2);
private:
    int _start;
    int _end;
    float _saving;
};

#endif //MTVRPTWSC_LINK_H

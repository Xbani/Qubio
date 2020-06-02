#ifndef QULISTBLOCK_H
#define QULISTBLOCK_H

#include<QtCore>

class QuListBlock : public QObject
{
      Q_OBJECT
public:
     QuListBlock();
     enum SolidBlock {Error,
                      Stone,
                      WoodPlank,
                      Grass,
                      Stairs, Cloud, Bridge
                     };
     Q_ENUM(SolidBlock);

    QString getBlockName(QuListBlock::SolidBlock value);
    QString getBlockFile(QuListBlock::SolidBlock value);
    int getNumberOfSolidBlock();
private:
     QMetaEnum metaEnum;
     const QString FILE_PATH = ":/resources/sprites/blocks/";

};

#endif // QULISTBLOCK_H

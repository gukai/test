# -*- coding: utf-8    -*-
from django.db import models

# Create your models here.
class Products(models.Model):
    name = models.CharField('图书名称', max_length=20)
    publish = models.CharField('出版社', max_length=20)
    price = models.FloatField('出版社', max_length=255)

    def __unicode__(self):
        return '%s'%(self.name)

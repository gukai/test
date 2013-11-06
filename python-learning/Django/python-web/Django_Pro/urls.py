from django.conf.urls.defaults import patterns, include, url

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'Django_Pro.views.home', name='home'),
    # url(r'^Django_Pro/', include('Django_Pro.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    url(r'^admin/', include(admin.site.urls)),
    url(r'^login/', 'Django_Pro.views.login'),
    url(r'^pro/', 'Products.views.proList'),
    url(r'^buy/', 'Products.views.buypro'),
    
)

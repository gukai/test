from django.shortcuts import render_to_response
from Django_Pro.Products.models import Products
from django.template import RequestContext
# Create your views here.

def proList(request):
    pros = Products.objects.all()
    return render_to_response('pro_index.html', {'pros':pros})

def buypro(request):
    proId = request.GET.get('proId', None)
    if proId > 0:
        pro=Products.objects.get(id=proId)
        request.session['pro']=pro
        return render_to_response('showBuy.html', context_instance=RequestContext(request))
    return render_to_response('showBuy.html')

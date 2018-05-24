import urllib
import HTMLParser

def HTML_load(url): #función para cargar la página
    with urllib.request.urlopen('url') as webDump:
        statPage = webDump.read() #urllib busca la pagina y y la guarda como variable

def HTML_parse(page):
    commaSepVal = 

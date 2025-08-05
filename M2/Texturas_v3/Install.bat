echo Criando ambiente virtual com venv ...
python -m venv OpenGL

echo Ativando ambiente virtual ...
call "OpenGL\Scripts\activate"


echo Instalando numpy ...
pip install numpy

echo Instalando pillow ...
pip install pillow

echo Instalando PyOpenGL ...
git clone https://github.com/mcfletch/pyopengl
cd pyopengl
pip install -e .
cd ..

echo Instalação concluida!

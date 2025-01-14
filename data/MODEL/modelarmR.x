xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 34;
 -80.15261;227.76843;-23.52349;,
 -63.13181;220.72559;-15.89425;,
 -96.45509;138.37833;-17.56707;,
 -113.47596;145.42120;-25.19630;,
 -56.18986;217.54224;2.52291;,
 -89.51316;135.19510;0.85009;,
 -63.39330;220.08316;20.93948;,
 -96.71663;137.73592;19.26666;,
 -80.52247;226.85986;28.56728;,
 -113.84582;144.51263;26.89447;,
 -97.54333;233.90274;20.93805;,
 -130.86665;151.55548;19.26523;,
 -104.48527;237.08600;2.52089;,
 -137.80858;154.73883;0.84807;,
 -97.28180;234.54515;-15.89568;,
 -130.60515;152.19791;-17.56850;,
 -80.15261;227.76843;-23.52349;,
 -113.47596;145.42120;-25.19630;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -80.33756;227.31409;2.52190;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;,
 -113.66087;144.96695;0.84908;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;;
 
 MeshMaterialList {
  1;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  26;
  0.375054;0.926812;0.018828;,
  0.007099;0.017438;-0.999823;,
  0.660491;-0.252919;-0.706953;,
  0.926977;-0.375119;0.000039;,
  0.650452;-0.277580;0.707009;,
  -0.007098;-0.017438;0.999823;,
  -0.660491;0.252919;0.706953;,
  -0.926977;0.375119;-0.000039;,
  -0.650452;0.277580;-0.707009;,
  -0.375054;-0.926812;-0.018828;,
  0.375053;0.926812;0.018830;,
  0.375054;0.926812;0.018831;,
  0.375052;0.926812;0.018827;,
  0.375052;0.926813;0.018826;,
  0.375054;0.926812;0.018826;,
  0.375055;0.926811;0.018825;,
  0.375054;0.926812;0.018827;,
  0.375054;0.926812;0.018831;,
  -0.375054;-0.926812;-0.018827;,
  -0.375054;-0.926812;-0.018825;,
  -0.375052;-0.926812;-0.018827;,
  -0.375053;-0.926812;-0.018831;,
  -0.375054;-0.926812;-0.018830;,
  -0.375054;-0.926812;-0.018829;,
  -0.375053;-0.926812;-0.018827;,
  -0.375053;-0.926812;-0.018827;;
  24;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,10,11;,
  3;0,12,10;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,11,17;,
  3;9,18,19;,
  3;9,19,20;,
  3;9,20,21;,
  3;9,21,22;,
  3;9,22,23;,
  3;9,23,24;,
  3;9,24,25;,
  3;9,25,18;;
 }
 MeshTextureCoords {
  34;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}

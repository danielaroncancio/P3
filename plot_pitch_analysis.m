% plot_pitch_analysis

% Carregar l'àudio i seleccionar un segment de 30 ms
[y, Fs] = audioread('pav_137.wav'); % Carregar fitxer d'àudio
durada = 0.03; % Durada en segons (30 ms)
mostres = round(durada * Fs); % Nombre de mostres en 30 ms
inici = round(0.70 * length(y)); % Punt inicial del segment
final = inici + mostres - 1; % Punt final del segment

% Seleccionar el segment de la senyal
segment = y(inici:final);

% Subplot 1: Senyal temporal
subplot(2, 1, 1);
plot((0:mostres-1) / Fs, segment);
title('Senyal temporal (30 ms)');
xlabel('Temps (s)');
ylabel('Amplitud');
grid on;

% Calcular l'autocorrelació de la senyal
autocorrelacio = xcorr(segment, 'coeff'); % Autocorrelació normalitzada
lags = (-mostres+1:mostres-1) / Fs; % Lags en segons

% Identificar el primer màxim secundari
[peaks, locations] = findpeaks(autocorrelacio(mostres:end), 'MinPeakProminence', 0.1); % Només màxims després del zero
if isempty(peaks)
    error('No s''han trobat màxims secundaris a l''autocorrelació. Ajusta els paràmetres.');
end
primer_maxim = locations(1) + mostres - 1; % Posició del primer màxim secundari al vector original
retard = lags(primer_maxim); % Retard en segons (correspon al període del pitch)

% Subplot 2: Autocorrelació
subplot(2, 1, 2);
plot(lags, autocorrelacio);
hold on;
stem(lags(primer_maxim), autocorrelacio(primer_maxim), 'r', 'Marker', 'o', 'MarkerSize', 7); % Marcar primer màxim secundari
title('Autocorrelació amb primer màxim secundari marcat');
xlabel('Retard (s)');
ylabel('Coeficient d''autocorrelació');
legend(sprintf('Primer màxim: %.4f s', retard));
grid on;

% Mostrar el període de pitch a la primera gràfica
subplot(2, 1, 1);
text(0.5 * retard, 0.8 * max(segment), sprintf('Pitch: %.2f Hz', 1 / retard), 'Color', 'r');

